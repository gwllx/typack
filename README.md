# Type Pack

A compile-time API for working with type template parameter packs.

## Example

```cpp
#include "typack/typack.hpp"

int main() {
    using pack = ty::pack<char, int>;

    // head_t - First type in the pack
    static_assert(std::is_same_v<pack::head_t, char>);

    // tail_t - Pack of types after the first type
    static_assert(std::is_same_v<pack::tail_t, ty::pack<int>>);

    // at<N> - Type at position N
    static_assert(std::is_same_v<pack::at_t<1>, int>);

    // concat<Ts...> - Add types to the end of the pack
    static_assert(std::is_same_v<pack::concat_t<int>,
            ty::pack<char, int, int>>);

    // remove_t<Ts...> - Remove types from the pack
    static_assert(std::is_same_v<pack::remove_t<int>, ty::pack<char>>);

    // contains_any_v<Ts...> - true if pack contains any of the given types
    static_assert(pack::contains_any_v<int>);
    static_assert(!pack::contains_any_v<double>);
    
    // contains_all_v<Ts...> - true if the pack contains all given types
    static_assert(pack::contains_all_v<int, char>);
    static_assert(!pack::contains_all_v<int, double>);

    // size - Size of the pack
    std::cout << "pack size: " << pack::size << std::endl; // pack size: 2
}
```

See the [tests](./test/typack_test.cpp) for more examples.
