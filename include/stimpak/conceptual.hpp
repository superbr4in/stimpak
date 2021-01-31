#pragma once

#include <ranges>

namespace sti
{
    template <typename Value>
    concept integral_or_enum = std::integral<Value> || std::is_enum_v<Value>;

    template <typename Value>
    concept decayed = std::is_same_v<Value, std::decay_t<Value>>;
    template <typename Value>
    concept decayed_integral = decayed<Value> && std::integral<Value>;
    template <typename Value>
    concept decayed_integral_or_enum = decayed<Value> && integral_or_enum<Value>;

    template <typename T, typename Value>
    concept forward_range_of = std::ranges::forward_range<T> && std::same_as<Value, std::ranges::range_value_t<T>>;
    template <typename T, typename Value>
    concept random_access_range_of = std::ranges::random_access_range<T> && std::same_as<Value, std::ranges::range_value_t<T>>;
}
