# STImPak

**S**tandard **T**emplate library **Im**provement **Pa**c**k**age

This is a header-only project on the `C++20` language standard without further requirements.

## Features

Use the desired header files present in the [include directory](include/stimpak/). Any functionality is addressable through the `sti` namespace.

| Header                                                       | Purpose                                                                                                                                         |
| ------------------------------------------------------------ | ----------------------------------------------------------------------------------------------------------------------------------------------- |
| [`binary.hpp`](include/stimpak/binary.hpp)                   | Information regarding binary data representation                                                                                                |
| [`comparison.hpp`](include/stimpak/comparison.hpp)           | Reusable comparators for straightforward sequence sorting                                                                                       |
| [`conceptual.hpp`](include/stimpak/conceptual.hpp)           | Versatile concepts                                                                                                                              |
| [`container.hpp`](include/stimpak/container.hpp)             | Operations on various STL containers                                                                                                            |
| [`fixed_algorithm.hpp`](include/stimpak/fixed_algorithm.hpp) | Algoritms using compile-time constant bounds                                                                                                    |
| [`function_traits.hpp`](include/stimpak/function_traits.hpp) | Function information through pointers                                                                                                           |
| [`packing.hpp`](include/stimpak/packing.hpp)                 | Template parameter pack concepts                                                                                                                |
| [`propagation.hpp`](include/stimpak/propagation.hpp)         | Easy constant propagation                                                                                                                       |
| [`sfinae.hpp`](include/stimpak/sfinae.hpp)                   | [**S**ubstitution **F**ailure **I**s **N**ot **A**n **E**rror](https://en.wikipedia.org/wiki/Substitution_failure_is_not_an_error) realizations |
| [`streaming.hpp`](include/stimpak/streaming.hpp)             | Stream extraction extensions                                                                                                                    |
| [`variation.hpp`](include/stimpak/variation.hpp)             | Simple `std::variant` processing                                                                                                                |

Refer to the documentation comments in the code files for detailed information about the respective implementations.
