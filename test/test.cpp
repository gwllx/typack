#include "typack/typack.hpp"
#include <tuple>

#define ASSERT_SAME(...) static_assert(std::is_same_v<__VA_ARGS__>)

void testHeadTail() {
    using pack = ty::pack<char, short, int, long>;
    ASSERT_SAME(pack::head_t, char);
    ASSERT_SAME(pack::tail_t, ty::pack<short, int, long>);

    using pack2 = ty::pack<double>;
    ASSERT_SAME(pack2::head_t, double);
    ASSERT_SAME(pack2::tail_t, ty::empty_t);
}

void testAt() {
    using pack = ty::pack<char, short, int, long>;
    ASSERT_SAME(pack::at_t<0>, char);
    ASSERT_SAME(pack::at_t<1>, short);
    ASSERT_SAME(pack::at_t<2>, int);
    ASSERT_SAME(pack::at_t<3>, long);
}

void testConcat() {
    ASSERT_SAME(ty::empty_t::concat_t<>, ty::pack<>);
    ASSERT_SAME(ty::empty_t::concat_t<int>, ty::pack<int>);
    ASSERT_SAME(ty::empty_t::concat_t<int, double>, ty::pack<int, double>);

    using pack = ty::pack<char, short>;
    ASSERT_SAME(pack::concat_t<int>, ty::pack<char, short, int>);
    ASSERT_SAME(pack::concat_t<pack>, ty::pack<char, short, char, short>);
}

void testAny() {
    static_assert(!ty::empty_t::any_v<std::is_same, void>);

    using pack = ty::pack<int, float, double>;
    static_assert(pack::any_v<std::is_same, int>);
    static_assert(!pack::any_v<std::is_same, char>);
}

void testAll() {
    static_assert(ty::empty_t::all_v<std::is_same, int>);

    using pack = ty::pack<double, float>;
    static_assert(pack::all_v<std::is_floating_point>);
    static_assert(!pack::all_v<std::is_integral>);
}

void testMap() {
    using pack = ty::pack<const short, const int, const long>;
    ASSERT_SAME(pack::map_t<std::remove_const>, ty::pack<short, int, long>);
}

void testFilter() {
    using pack = ty::pack<double, float, int, float, short>;
    ASSERT_SAME(pack::filter_t<std::is_integral>, ty::pack<int, short>);
}

void testInto() {
    using pack = ty::pack<char, int, double>;
    ASSERT_SAME(pack::into_t<std::tuple>, std::tuple<char, int, double>);
}

int main() {
    testHeadTail();
    testAt();
    testConcat();
    testAny();
    testAll();
    testMap();
    testFilter();
    testInto();
}
