#pragma once

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
}
