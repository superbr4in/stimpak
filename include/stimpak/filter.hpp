#pragma once

#include <tuple>
#include <variant>
#include <vector>

namespace sti
{
    template <typename... Ts>
    inline std::tuple<std::vector<Ts>...> filter(std::vector<std::variant<Ts...>> variants)
    {
        std::tuple<std::vector<Ts>...> filtered;

        for (auto const& variant : variants)
        {
            std::visit(
                [&filtered](auto&& value)
                {
                    std::get<std::vector<std::decay_t<decltype(value)>>>(filtered).push_back(value);
                },
                variant);
        }

        return filtered;
    }
}
