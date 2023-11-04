# Type Pack

A compile-time API for manipulation of C++ type template parameter packs. 

## Example

```cpp
#include "typack/typack.hpp"
#include <tuple>
#include <type_traits>

int main() {
    using tuple = ty::pack<char, short, double>;
            ::filter_t<std::is_integral>
            ::concat_t<int>
            ::into_t<std::tuple>; // std::tuple<char, short, int>
}
```

See [API Overview](./docs/api-overview.md) or
[Class List](https://gwllx.github.io/typack/annotated.html) for more
information.
