# Type Pack

Experiments in compile-time manipulation of template parameter packs.

## Example

```cpp
#include "typack/typack.hpp"
#include <type_traits>

int main() {
    using pack = ty::pack<char, int, float>;

    static_assert(std::is_same_v<pack::head, char>):
    static_assert(std::is_same_v<pack::at<1>, int>):
    static_assert(std::is_same_v<pack::tail, ty::pack<int, float>>):
    
    std::cout << "pack size: " << pack::size << std::endl; // pack size: 3
}
```
