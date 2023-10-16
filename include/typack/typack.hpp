#ifndef TYPACK_H
#define TYPACK_H

#include <cstddef>

namespace ty {

template<typename ...> struct pack;

///
/// Empty specialisation
///
template<>
struct pack<> {
    static constexpr auto size = std::size_t{0};

    ///
    /// Concat
    ///
    template<typename ...Ts>
    struct concat { using type = pack<Ts...>; };

    template<typename ...Ts>
    struct concat<pack<Ts...>> { using type = pack<Ts...>; };

    template<typename ...Ts>
    using concat_t = typename concat<Ts...>::type;

    ///
    /// Remove
    ///
    template<typename ...Ts>
    struct remove { using type = pack<>; };

    template<typename ...Ts>
    using remove_t = typename remove<Ts...>::type;
};

using empty_t = pack<>;

///
/// Main specialisation
///
template<typename Head, typename ...Tail>
struct pack<Head, Tail...> {
    static constexpr auto size = sizeof...(Tail) + std::size_t{1};

    using head_t = Head;
    using tail_t = pack<Tail...>;

    ///
    /// Random access
    ///
    template<std::size_t N>
    struct at {
        using type = typename tail_t::template at<N - 1>::type;
    };

    template<> struct at<0> { using type = head_t; };
    template<std::size_t N> using at_t = typename at<N>::type;

    ///
    /// Concat
    ///
    template<typename ...Ts>
    struct concat {
        using type = pack<Head, Tail..., Ts...>;
    };

    template<typename ...Ts>
    struct concat<pack<Ts...>> { using type = typename concat<Ts...>::type; };

    template<typename ...Ts>
    using concat_t = typename concat<Ts...>::type;

    ///
    /// Remove
    ///
    template<typename...> struct remove;

    template<typename First, typename ...Ts>
    struct remove<First, Ts...> {
        using rm_tail_t = typename tail_t::template remove<First>::type;
        using rm_first_t = typename pack<Head>::template concat_t<rm_tail_t>;
        using type = typename rm_first_t::template remove<Ts...>::type;
    };

    template<typename ...Ts>
    struct remove<Head, Ts...> {
        using type = typename tail_t::template remove<Head, Ts...>::type;
    };

    template<>
    struct remove<> { using type = pack<Head, Tail...>; };

    template<typename ...Ts>
    struct remove<pack<Ts...>> { using type = typename remove<Ts...>::type; };

    template<typename ...Ts>
    using remove_t = typename remove<Ts...>::type;
};

} // namespace ty

#endif // TYPACK_H
