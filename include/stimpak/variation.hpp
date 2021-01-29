#pragma once

#include <variant>
#include <vector>

#include <stimpak/packing.hpp>

namespace sti
{
    template <typename, typename>
    struct type_of_variant_checker
    { };
    template <typename T, typename... Us>
    struct type_of_variant_checker<T, std::variant<Us...>> : type_of_pack_checker<T, Us...>
    { };
    template <typename T, typename Variant>
    concept type_of_variant = type_of_variant_checker<T, Variant>::value;

    template <typename, typename>
    struct type_of_common_variant_checker
    { };
    template <typename T, template <typename> typename U, typename... Vs>
    struct type_of_common_variant_checker<T, std::variant<U<Vs>...>> : type_of_variant_checker<U<T>, std::variant<U<Vs>...>>
    { };
    template <typename T, typename Variant>
    concept type_of_common_variant = type_of_common_variant_checker<T, Variant>::value;

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
