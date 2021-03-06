#pragma once

#include <stimpak/sfinae.hpp>

namespace sti
{
    /*!
     *  Universal comparator with the ability to dereference pointers and
     *  other wrapping types for comparison.
     */
    struct wrap_comparator
    {
        using is_transparent = std::true_type;

        template <typename T1, typename T2>
        inline bool operator()(T1&& value1, T2&& value2) const
        {
            auto const indirection =
                [](auto&& value)
                    -> decltype(*value)
                {
                    return *value;
                };

            return
                sfiid(indirection, value1)() <
                sfiid(indirection, value2)();
        }
    };
}
