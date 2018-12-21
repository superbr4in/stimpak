# STImPak

**S**tandard **T**emplate library **Im**provement **Pa**c**k**age

This is a header-only project without further requirements except the `C++17` language standard.

## Features

Use the desired header files present in the [include directory](include/stimpak/). Any functionality is addressable through the `sti` namespace.

| Header                                             | Purpose                                                           |
| -------------------------------------------------- | ----------------------------------------------------------------- |
| [`comparison.hpp`](include/stimpak/comparison.hpp) | Reusable comparators for sequence sorting                         |
| [`filter.hpp`](include/stimpak/filter.hpp)         | Simple `std::variant` processing                                  |
| [`sfinae.hpp`](include/stimpak/sfinae.hpp)         | [**S**ubstitution **F**ailure **I**s **N**ot **A**n **E**rror](https://en.wikipedia.org/wiki/Substitution_failure_is_not_an_error) realizations |
| [`visitor.hpp`](include/stimpak/visitor.hpp)       | `std::visit` extensions                                           |

Refer to the documentation comments in the code files for further information.
