#include "typack/typack.hpp"
#include <type_traits>

#define IS_SAME(...) static_assert(std::is_same_v<__VA_ARGS__>)

int main() {
    using namespace ty;
    using uut = pack<int, float, char>; // Unit under test

    static_assert(uut::size == std::size_t{3});
    IS_SAME(uut::head_t, int);
    IS_SAME(uut::tail_t, pack<float, char>);

    static_assert(empty_t::size == 0);
    IS_SAME(pack<>, empty_t);

    // Random access
    IS_SAME(uut::at_t<0>, int);
    IS_SAME(uut::at_t<1>, float);
    IS_SAME(uut::at_t<2>, char);

    // Concat
    IS_SAME(empty_t::concat_t<int>, pack<int>);
    IS_SAME(empty_t::concat_t<float, double>, pack<float, double>);
    IS_SAME(empty_t::concat_t<pack<char, int>>, pack<char, int>);

    IS_SAME(uut::concat_t<double>, pack<int, float, char, double>);
    IS_SAME(uut::concat_t<float, int>, pack<int, float, char, float, int>);

    using uut2 = pack<int, double>;
    IS_SAME(uut::concat_t<uut2>, pack<int, float, char, int, double>);

    // Remove
    IS_SAME(empty_t::remove_t<>, empty_t);
    IS_SAME(empty_t::remove_t<double>, empty_t);
    IS_SAME(empty_t::remove_t<pack<int, char>>, empty_t);

    IS_SAME(uut::remove_t<float>, pack<int, char>);
    IS_SAME(uut::remove_t<int, char>, pack<float>);
    IS_SAME(uut::remove_t<pack<char, float>>, pack<int>);

    IS_SAME(uut::remove_t<int, float, char>, empty_t);
    IS_SAME(uut::remove_t<double>, uut);

    // Something silly...
    IS_SAME(char,
            pack<int, char>
                ::concat_t<pack<float, double>>
                ::remove_t<float>
                ::tail_t
                ::head_t);
    
    // Contains
    static_assert(uut::contains_any_v<int>);
    static_assert(uut::contains_any_v<float>);
    static_assert(uut::contains_any_v<char>);
    static_assert(uut::contains_any_v<ty::pack<int, double>>);

    static_assert(!uut::contains_any_v<double>);
    static_assert(!uut::contains_any_v<>);
    static_assert(!uut::contains_any_v<ty::pack<double, short>>);
    static_assert(!uut::contains_any_v<ty::empty_t>);

    return 0;
}
