# typack – Type Pack

A compile-time API for working with type template parameter packs.

## Example

```cpp
#include "typack/typack.hpp"
#include <tuple>

int main() {
    using tuple = ty::pack<char, short, double>;
            ::filter_t<std::is_integral>
            ::concat_t<int>
            ::into_t<std::tuple>; // std::tuple<char, short, int>
}
```

See the [docs](https://gwllx.github.io/typack) for more information.
