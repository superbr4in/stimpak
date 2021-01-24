#pragma once

#include <climits>
#include <concepts>

#define widthof(T) sti::conditional<std::same_as<T, bool>, 1, sizeof(T) * CHAR_BIT>::VALUE

namespace sti
{
    template <bool, std::size_t, std::size_t>
    struct conditional;

    template <std::size_t VALUE_TRUE, std::size_t VALUE_FALSE>
    struct conditional<true, VALUE_TRUE, VALUE_FALSE>
    {
        static std::size_t constexpr VALUE = VALUE_TRUE;
    };
    template <std::size_t VALUE_TRUE, std::size_t VALUE_FALSE>
    struct conditional<false, VALUE_TRUE, VALUE_FALSE>
    {
        static std::size_t constexpr VALUE = VALUE_FALSE;
    };
}

#ifdef LINT
static_assert(widthof(bool) == 1);
static_assert(widthof(char) == CHAR_BIT);
#endif
