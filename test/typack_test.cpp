#include "typack/typack.hpp"
#include <type_traits>

int main() {
    using uut = ty::pack<int, float, char>;

    static_assert(ty::empty::size == 0);
    static_assert(std::is_same_v<ty::pack<>, ty::empty>);
    static_assert(uut::size == 3);
    static_assert(std::is_same_v<uut::head, int>);
    static_assert(std::is_same_v<uut::tail, ty::pack<float, char>>);
    static_assert(std::is_same_v<uut::at<0>, int>);
    static_assert(std::is_same_v<uut::at<1>, float>);
    static_assert(std::is_same_v<uut::at<2>, char>);

    return 0;
}
