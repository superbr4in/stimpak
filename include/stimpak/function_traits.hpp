#pragma once

#include <tuple>

#include <stimpak/conceptual.hpp>

namespace sti
{
    template <typename>
    struct function_traits { };
    template <typename Result, typename... Arguments>
    struct function_traits<Result (*)(Arguments...)>
    {
        static std::size_t constexpr ARGUMENT_COUNT = sizeof...(Arguments);

        using result_type = Result;
        template <std::size_t INDEX> requires (INDEX < ARGUMENT_COUNT)
        using argument_type = std::tuple_element_t<INDEX, std::tuple<Arguments...>>;
    };
    template <decayed T, typename Result, typename... Arguments>
    struct function_traits<Result (T::*)(Arguments...)> : function_traits<Result (*)(Arguments...)> { };
    template <decayed T, typename Result, typename... Arguments>
    struct function_traits<Result (T::*)(Arguments...) const> : function_traits<Result (T::*)(Arguments...)> { };

    template <typename Function>
    using result_type = typename function_traits<Function>::result_type;
    template <typename Function, std::size_t INDEX> requires (INDEX < function_traits<Function>::ARGUMENT_COUNT)
    using argument_type = typename function_traits<Function>::template argument_type<INDEX>;

    template <typename>
    class member_function { };
    template <decayed T, typename Result, typename... Arguments>
    class member_function<Result (T::*)(Arguments...)>
    {
        T* instance_;
        Result (T::* function_)(Arguments...);

    public:

        member_function(T* const instance, Result (T::* const function)(Arguments...)) :
            instance_(instance),
            function_(function)
        { }

        Result operator()(Arguments... arguments) const
        {
            return (instance_->*function_)(std::forward<Arguments...>(arguments)...);
        }
    };
    template <decayed T, typename Result, typename... Arguments>
    class member_function<Result (T::*)(Arguments...) const>
    {
        T const* instance_;
        Result (T::* function_)(Arguments...) const;

    public:

        member_function(T const* const instance, Result (T::* const function)(Arguments...) const) :
            instance_(instance),
            function_(function)
        { }

        Result operator()(Arguments... arguments) const
        {
            return (instance_->*function_)(std::forward<Arguments...>(arguments)...);
        }
    };

    template <typename T, typename Function>
    member_function(T*, Function) -> member_function<Function>;
    template <typename T, typename Function>
    member_function(T const*, Function) -> member_function<Function>;
}
