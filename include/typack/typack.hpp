/// \file include/typack/typack.hpp
#ifndef TYPACK_H
#define TYPACK_H

#include <cstddef>
#include <type_traits>

/// \brief Type Pack
namespace ty {

/// \brief A wrapper for a type template parameter pack
/// \tparam ... Pack types
template<typename ...> struct pack;

/// \brief Implementation details
namespace detail {

/// \cond DETAIL
/// \brief Provides the member typedef type which wraps Ts in a pack
/// \tparam ...Types Pack types
template<typename ...Ts>
struct pack_type : std::type_identity<pack<Ts...>> {};

/// \brief Provides a member typedef type which wraps T in a pack
/// (dependent on Filter)
template<typename T, bool Filter> struct filter_pack;

/// \brief Provides a member typedef type which wraps T in a pack
/// \tparam T Pack type
template<typename T>
struct filter_pack<T, true> : pack_type<T> {};

/// \brief Provides a member typedef type which is the empty pack
/// \tparam T Pack type (unused)
template<typename T>
struct filter_pack<T, false> : pack_type<> {};
/// \endcond

/// \brief Provides common pack functionality
/// \tparam ...Ts Pack types
template<typename ...Ts>
struct pack_base {
  /// \brief Number of types in this pack
  static constexpr auto size = sizeof...(Ts);

  /// \brief Provides a member typedef type which is this pack with Us added
  /// \tparam ...Us New types
  /// \details Prefer the use \ref concat_t over this struct.
  template<typename ...Us>
  struct concat : pack_type<Ts..., Us...> {};

  /// \brief Provides a member typedef type which is this pack with the
  /// inner pack types Us added
  /// \tparam ...Us Inner pack types
  /// \details Prefer the use \ref concat_t over this struct.
  template<typename ...Us>
  struct concat<pack<Us...>> : concat<Us...> {};

  /// \brief Helper type which is this pack with Us added
  /// \tparam ...Us New types
  template<typename ...Us>
  using concat_t = typename concat<Us...>::type;

  /// \brief Provides a static constant which indicates whether any type in
  /// this pack matches Trait
  /// \tparam Trait Type trait
  /// \tparam ...Us Trait type parameters
  /// \details Prefer to use \ref any_v over this struct.
  template<template<typename ...> typename Trait, typename ...Us>
  struct any : std::integral_constant<bool,
      (Trait<Ts, Us...>::value || ...)> {};

  /// \brief Helper variable which checks whether any type in this pack
  /// matches Trait
  /// \tparam Trait Type trait
  /// \tparam ...Us Trait type parameters
  template<template<typename ...> typename Trait, typename ...Us>
  static constexpr auto any_v = any<Trait, Us...>::value;

  /// \brief Provides a static constant which indicates whether all types
  /// in this pack match Trait
  /// \tparam Trait Type trait
  /// \tparam ...Us Trait type parameters
  /// \details Prefer to use \ref all_v over this struct.
  template<template<typename ...> typename Trait, typename ...Us>
  struct all : std::integral_constant<bool,
      (Trait<Ts, Us...>::value && ...)> {};

  /// \brief Helper variable which checks whether all types in this pack
  /// match Trait
  /// \tparam Trait Type trait
  /// \tparam ...Us Trait type parameters
  template<template<typename ...> typename Trait, typename ...Us>
  static constexpr auto all_v = all<Trait, Us...>::value;

  /// \brief Helper type which wraps this pack's types in Tuple
  /// \tparam Tuple Tuple-like type
  template<template<typename ...> typename Tuple>
  using into_t = Tuple<Ts...>;
};

} // namespace detail

/// \brief Empty pack specialization
template<>
struct pack<> : detail::pack_base<> {
  /// \cond DETAIL
  /// \brief Provides a false type for raising a static out of bounds error
  /// \tparam Pack index (unused)
  template<std::size_t>
  struct out_of_bounds : std::false_type {};

  /// \brief Provides an out of bounds error message
  /// \tparam I Pack index
  template<std::size_t I>
  struct at {
    static_assert(out_of_bounds<I>::value, "pack index out of bounds");
  };
  /// \endcond

  /// \brief Provides a member typedef type which is the empty pack
  /// \details Prefer to use \ref map_t over this struct.
  template<template<typename ...> typename, typename ...>
  struct map : detail::pack_type<> {};

  /// \brief Helper type which transforms each type in this pack with Mod
  /// \tparam Mod Type modifier
  /// \tparam ...Ts Mod type parameters
  template<template<typename ...> typename Mod, typename ...Ts>
  using map_t = typename map<Mod, Ts...>::type;

  /// \brief Provides a member typedef type which is the empty pack
  /// \details Prefer to use \ref filter_t over this struct.
  template<template<typename ...> typename, typename ...>
  struct filter : detail::pack_type<> {};

  /// \brief Helper type which filters the types in this pack matching Trait
  /// \tparam Trait Type trait
  /// \tparam ...Ts Trait type parameters
  template<template<typename ...> typename Trait, typename ...Ts>
  using filter_t = typename filter<Trait, Ts...>::type;
};

/// \brief Main pack specialization
/// \tparam Head First type in the pack
/// \tparam ...Tail All other types in the pack
template<typename Head, typename ...Tail>
struct pack<Head, Tail...> : detail::pack_base<Head, Tail...> {
  /// \brief First type in this pack
  using head_t = Head;

  /// \brief Pack of all types in this pack, except for the first
  using tail_t = pack<Tail...>;

  /// \brief Provides a member typedef type which is the type at pack index I
  /// \tparam I Pack index
  /// \details Prefer to use \ref at_t over this struct.
  template<std::size_t I>
  struct at : std::type_identity<
      typename tail_t::template at<I - 1>::type> {};

  /// \brief Provides a member typedef type which is the type at pack index 0
  /// \details Prefer to use \ref at_t over this struct.
  template<>
  struct at<0> : std::type_identity<Head> {};

  /// \brief Helper type which is the type at pack index I
  /// \tparam I Pack index
  template<std::size_t I>
  using at_t = typename at<I>::type;

  /// \brief Provides a member typedef type which is all types in this pack
  /// transformed by Mod
  /// \tparam Mod Type modifier
  /// \tparam ...Ts Mod type parameters
  /// \details Prefer to use \ref map_t over this struct.
  template<template<typename ...> typename Mod, typename ...Ts>
  struct map : std::type_identity<
      typename pack<typename Mod<Head, Ts...>::type>::template concat_t<
          typename tail_t::template map<Mod, Ts...>::type>> {};

  /// \brief Helper type which is all types in this pack transformed by Mod
  /// \tparam Mod Type modifier
  /// \tparam ...Ts Mod type parameters
  template<template<typename ...> typename Mod, typename ...Ts>
  using map_t = typename map<Mod, Ts...>::type;

  /// \brief Provides a member typedef type which is a pack with all types in
  /// this pack that match Trait
  /// \tparam Trait Type trait
  /// \tparam ...Ts Trait type parameters
  /// \details Prefer to use \ref filter_t over this struct.
  template<template<typename ...> typename Trait, typename ...Ts>
  struct filter : std::type_identity<
      typename detail::filter_pack<Head, Trait<Head, Ts...>::value>::type
          ::template concat_t<typename tail_t
              ::template filter<Trait, Ts...>::type>> {};

  /// \brief Helper type which is a pack with all types in this pack that
  /// match Trait
  /// \tparam Trait Type trait
  /// \tparam ...Ts Trait type parameters
  template<template<typename ...> typename Trait, typename ...Ts>
  using filter_t = typename filter<Trait, Ts...>::type;
};

/// \brief Inner pack unwrapping specialization
/// \tparam ...Ts Inner pack types
template<typename ...Ts>
struct pack<pack<Ts...>> : pack<Ts...> {};

/// \brief Helper type which is the empty pack
using empty_t = pack<>;

} // namespace ty

#endif // TYPACK_H
