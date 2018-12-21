#pragma once

#include <variant>
#include <vector>

namespace sti
{
    /*!
     *  Helper type to provide multiple lambdas to the \c std::visit function.
     */
    template <typename... Ts>
    struct generic_visitor : Ts...
    {
        using Ts::operator()...;
    };
    template <typename... Ts>
    generic_visitor(Ts...) -> generic_visitor<Ts...>;

    /*!
     *  Transfers the values of a sequence containing diverse types to multiple sequences with
     *  each containing one certain type.
     */
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
