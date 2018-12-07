#pragma once

namespace stim
{
    template <typename... Ts>
    struct generic_visitor : Ts...
    {
        using Ts::operator()...;
    };

    template <typename... Ts>
    generic_visitor(Ts...) -> generic_visitor<Ts...>;
}
