# Type Pack

A compile-time API for working with type template parameter packs.

## Example

```cpp
#include "typack/typack.hpp"
#include <type_traits>

int main() {
    using pack = ty::pack<char, int>;

    static_assert(
        std::is_same_v<pack::head_t, char> &&
        std::is_same_v<pack::tail_t, ty::pack<int>> &&
        std::is_same_v<pack::at_t<1>, int> &&
        std::is_same_v<pack::concat_t<int>, ty::pack<char, int, int>> &&
        std::is_same_v<pack::remove_t<int>, ty::pack<char>>
    );

    std::cout << "pack size: " << pack::size << std::endl; // pack size: 2
}
```

For more examples, see the [tests](./test/typack_test.cpp).
