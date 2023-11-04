# API Overview

## ty::pack

Provides a wrapper for a type template parameter pack.

```cpp
using pack = ty::pack<char, short, int>;
```

### Types (Transforms)

#### ty::pack::concat_t

Adds types to the end of a pack.

```cpp
static_assert(std::is_same_v<
    ty::pack<char, short>::concat_t<int>,
    ty::pack<char, short, int>
>);
```

``ty::pack::concat_t`` will also unwrap inner packs.

```cpp
static_assert(std::is_same_v<
    ty::pack<char, short>::concat_t<ty::pack<int>>,
    ty::pack<char, short, int>
>);
```

#### ty::pack::filter_t

Filters the types in a pack so that only those matching a given type trait
remain.

```cpp
static_assert(std::is_same_v<
    ty::pack<short, double, int>::filter_t<std::is_integral>,
    ty::pack<short, int>
>);
```

#### ty::pack::map_t

Transforms all types in a pack using a type modifier.

```cpp
static_assert(std::is_same_v<
    ty::pack<const char, const short>::map_t<std::remove_const>,
    ty::pack<char, short>
>);
```

#### ty::pack::into_t

Unwraps the pack types into another tuple-like template.

```cpp
static_assert(std::is_same_v<
    ty::pack<char, float, int>::into_t<std::tuple>,
    std::tuple<char, float, int>
>);
```

### Values

#### ty::pack::any_v

Provides a static boolean constant indicating whether any of the types in a pack
match a given type trait.

```cpp
static_assert(ty::pack<int, double>::any_v<std::is_floating_point> == true);
static_assert(ty::pack<char, int>::any_v<std::is_floating_point> == false);

// Empty pack any_v returns false
static_assert(ty::pack<>::any_v<std::is_integral> == false);
```

#### ty::pack::all_v

Provides a static boolean constant indicating whether all of the types in a pack
match a given type trait.

```cpp
static_assert(ty::pack<float, double>::any_v<std::is_floating_point> == true);
static_assert(ty::pack<int, double>::all_v<std::is_floating_point> == false);

// Empty pack all_v returns true
static_assert(ty::pack<>::all_v<std::is_integral> == true);
```

#### ty::pack::size

Provides the size of the pack.

```cpp
static_assert(ty::pack<char, int>::size == 2);
```

## ty::empty_t

Provides an empty pack (same as ``ty::pack<>``).
