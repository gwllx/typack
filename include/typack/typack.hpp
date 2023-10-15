#ifndef TYPACK_H
#define TYPACK_H

#include <cstddef>

namespace ty {

template<typename ...Ts>
struct pack {
    static constexpr auto size = sizeof...(Ts);
};

using empty = pack<>;

template<typename Head, typename ...Tail>
struct pack<Head, Tail...> {
    using head = Head;
    using tail = pack<Tail...>;
    static constexpr std::size_t size = sizeof...(Tail) + 1;

    template<std::size_t N>
    struct nth {
        using type = typename tail::template nth<N - 1>::type;
    };

    template<>
    struct nth<0> { using type = head; };

    template<std::size_t N>
    using at = typename nth<N>::type;
};

} // namespace ty

#endif // TYPACK_H
