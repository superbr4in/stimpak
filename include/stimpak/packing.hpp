#pragma once

#include <type_traits>

namespace sti
{
    template <typename T, typename U, typename... Us>
    struct type_of_pack_checker : std::conditional_t<std::is_same_v<T, U>, std::true_type, type_of_pack_checker<T, Us...>>
    { };
    template <typename T, typename U>
    struct type_of_pack_checker<T, U> : std::is_same<T, U>
    { };

    template <typename T, typename U, typename... Us>
    struct packed_same_as_checker : std::conditional_t<std::is_same_v<T, U>, packed_same_as_checker<T, Us...>, std::false_type>
    { };
    template <typename T, typename U>
    struct packed_same_as_checker<T, U> : std::is_same<T, U>
    { };
    template <typename T, typename... Us>
    concept packed_same_as = sizeof...(Us) == 0 || packed_same_as_checker<T, Us...>::value;
}
