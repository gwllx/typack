#ifndef TYPACK_H
#define TYPACK_H

#include <cstddef>
#include <type_traits>

namespace ty {

  /// \brief Represents a type template parameter pack.
  /// @tparam ... Parameter pack types
  template<typename ...> struct pack;

  namespace detail {

    template<typename ...Ts>
    struct pack_type : std::type_identity<pack<Ts...>> {};

    template<typename, bool> struct filter_pack;

    template<typename T>
    struct filter_pack<T, true> : pack_type<T> {};

    template<typename T>
    struct filter_pack<T, false> : pack_type<> {};

    template<typename ...Ts>
    struct pack_base {
      static constexpr auto size = sizeof...(Ts);

      template<typename ...Us>
      struct concat : pack_type<Ts..., Us...> {};

      template<typename ...Us>
      struct concat<pack<Us...>> : concat<Us...> {};

      template<typename ...Us>
      using concat_t = typename concat<Us...>::type;

      template<template<typename ...> typename Trait, typename ...Us>
      struct any : std::integral_constant<bool,
          (Trait<Ts, Us...>::value || ...)> {};

      template<template<typename ...> typename Trait, typename ...Us>
      static constexpr auto any_v = any<Trait, Us...>::value;

      template<template<typename ...> typename Trait, typename ...Us>
      struct all : std::integral_constant<bool,
          (Trait<Ts, Us...>::value && ...)> {};

      template<template<typename ...> typename Trait, typename ...Us>
      static constexpr auto all_v = all<Trait, Us...>::value;

      template<template<typename ...> typename Tuple>
      using into_t = Tuple<Ts...>;
    };

  } // namespace detail

  template<>
  struct pack<> : detail::pack_base<> {
    template<std::size_t>
    struct out_of_bounds : std::false_type {};

    template<std::size_t I>
    struct at {
      static_assert(out_of_bounds<I>::value, "pack index out of bounds");
    };

    template<template<typename ...> typename, typename ...>
    struct map : detail::pack_type<> {};

    template<template<typename ...> typename Trait, typename ...Ts>
    using map_t = typename map<Trait, Ts...>::type;

    template<template<typename ...> typename, typename ...>
    struct filter : detail::pack_type<> {};

    template<template<typename ...> typename Trait, typename ...Ts>
    using filter_t = typename filter<Trait, Ts...>::type;
  };

  template<typename Head, typename ...Tail>
  struct pack<Head, Tail...> : detail::pack_base<Head, Tail...> {
    using head_t = Head;
    using tail_t = pack<Tail...>;

    template<std::size_t I>
    struct at : std::type_identity<
        typename tail_t::template at<I - 1>::type> {};

    template<>
    struct at<0> : std::type_identity<Head> {};

    template<std::size_t I>
    using at_t = typename at<I>::type;

    template<template<typename ...> typename Trait, typename ...Us>
    struct map : std::type_identity<
        typename pack<typename Trait<Head, Us...>::type>::template concat_t<
            typename tail_t::template map<Trait, Us...>::type>> {};

    template<template<typename ...> typename Trait, typename ...Us>
    using map_t = typename map<Trait, Us...>::type;

    template<template<typename ...> typename Trait, typename ...Us>
    struct filter : std::type_identity<
        typename detail::filter_pack<Head, Trait<Head, Us...>::value>::type
            ::template concat_t<typename tail_t
                ::template filter<Trait, Us...>::type>> {};

    template<template<typename ...> typename Trait, typename ...Ts>
    using filter_t = typename filter<Trait, Ts...>::type;
  };

  /// \brief Pack specialization to unwrap an inner pack's types.
  /// @tparam ...Ts Inner pack types
  template<typename ...Ts>
  struct pack<pack<Ts...>> : pack<Ts...> {};

  /// \brief The empty pack.
  using empty_t = pack<>;

} // namespace ty

#endif // TYPACK_H
