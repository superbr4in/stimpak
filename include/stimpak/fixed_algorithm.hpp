#pragma once

#include <array>

#include <stimpak/conceptual.hpp>

namespace sti
{
    template <typename Callee, typename Value>
    concept generator =
        requires (Callee const& callee)
        {
            decayed<Value>;
            std::is_same_v<Value, decltype(callee.template operator()<std::size_t{0}>())>;
        };
    template <typename Callee, typename Value>
    concept aggregator =
        requires (Callee const& callee, Value const& value_1, Value const& value_2)
        {
            decayed<Value>;
            std::is_same_v<Value, decltype(callee.template operator()<std::size_t{0}>(value_1, value_2))>;
        };
    template <typename Callee, typename Value>
    concept procedure =
        requires (Callee const& callee, Value const& value)
        {
            decayed<Value>;
            std::is_same_v<void, decltype(callee.template operator()<std::size_t{0}>(value))>;
        };
    template <typename Callee>
    concept action =
        requires (Callee const& callee)
        {
            std::is_same_v<void, decltype(callee.template operator()<std::size_t{0}>())>;
        };

    namespace detail
    {
        template <decayed Value, std::size_t SIZE, generator<Value> Generator, decayed... Values> requires (SIZE > 0)
        static std::array<Value, SIZE> _make_array(Generator const& generator, Values... values)
        {
            static std::size_t constexpr INDEX{sizeof...(Values)};

            if constexpr (INDEX == SIZE)
                return { std::move(values)... };

            if constexpr (INDEX < SIZE)
            {
                return _make_array<Value, SIZE, Generator>(
                    generator,
                    std::move(values)...,
                    generator.template operator()<INDEX>());
            }
        }
        template <decayed Value, std::size_t SIZE, generator<Value> Generator, decayed... Values> requires (SIZE > 0)
        static std::array<Value, SIZE> _make_array_reversed(Generator const& generator, Values... values)
        {
            static std::size_t constexpr INDEX{sizeof...(Values)};

            if constexpr (INDEX == SIZE)
                return { std::move(values)... };

            if constexpr (INDEX < SIZE)
            {
                return _make_array_reversed<Value, SIZE, Generator>(
                    generator,
                    generator.template operator()<SIZE - INDEX - 1>(),
                    std::move(values)...);
            }
        }

        template <decayed Value, std::size_t SIZE, generator<Value> Generator, aggregator<Value> Aggregator, std::size_t INDEX> requires (SIZE > 0)
        static Value _aggregate_array(Generator const& generator, Aggregator const& aggregator, Value const& value)
        {
            if constexpr (INDEX == SIZE)
                return value;

            if constexpr (INDEX < SIZE)
            {
                return _aggregate_array<Value, SIZE, Generator, Aggregator, INDEX + 1>(
                    generator,
                    aggregator,
                    aggregator.template operator()<INDEX>(value, generator.template operator()<INDEX>()));
            }
        }

        template <decayed Value, std::size_t SIZE, procedure<Value> Procedure, std::size_t INDEX>
        static void _array_for_each(std::array<Value, SIZE> const& array, Procedure const& procedure)
        {
            if constexpr (INDEX < SIZE)
            {
                procedure.template operator()<INDEX>(std::get<INDEX>(array));
                _array_for_each<Value, SIZE, Procedure, INDEX + 1>(array, procedure);
            }
        }

        template <std::size_t SIZE, action Action, std::size_t INDEX>
        static void _fixed_loop(Action const& action)
        {
            if constexpr (INDEX < SIZE)
            {
                action.template operator()<INDEX>();
                _fixed_loop<SIZE, Action, INDEX + 1>(action);
            }
        }
        template <std::size_t SIZE, action Action, std::size_t INDEX>
        static void _fixed_loop_reversed(Action const& action)
        {
            if constexpr (INDEX < SIZE)
            {
                action.template operator()<SIZE - INDEX - 1>();
                _fixed_loop_reversed<SIZE, Action, INDEX + 1>(action);
            }
        }
    }

    template <decayed Value, std::size_t SIZE, generator<Value> Generator> requires (SIZE > 0)
    std::array<Value, SIZE> make_array(Generator const& generator)
    {
        return detail::_make_array<Value, SIZE, Generator>(generator, generator.template operator()<0>());
    }
    template <decayed Value, std::size_t SIZE, generator<Value> Generator> requires (SIZE > 0)
    std::array<Value, SIZE> make_array_reversed(Generator const& generator)
    {
        return detail::_make_array_reversed<Value, SIZE, Generator>(generator, generator.template operator()<SIZE - 1>());
    }

    template <decayed Value, std::size_t SIZE, generator<Value> Generator, aggregator<Value> Aggregator> requires (SIZE > 0)
    Value aggregate_array(Generator const& generator, Aggregator const& aggregator)
    {
        return detail::_aggregate_array<Value, SIZE, Generator, Aggregator, 1>(generator, aggregator, generator.template operator()<0>());
    }

    template <decayed Value, std::size_t SIZE, procedure<Value> Procedure>
    void array_for_each(std::array<Value, SIZE> const& array, Procedure const& procedure)
    {
        procedure.template operator()<0>(std::get<0>(array));
        detail::_array_for_each<Value, SIZE, Procedure, 1>(array, procedure);
    }

    template <std::size_t SIZE, action Action>
    void fixed_loop(Action const& action)
    {
        detail::_fixed_loop<SIZE, Action, 0>(action);
    }
    template <std::size_t SIZE, action Action>
    void fixed_loop_reversed(Action const& action)
    {
        detail::_fixed_loop_reversed<SIZE, Action, 0>(action);
    }
}

#ifdef LINT
struct mock_generator
{
    template <std::size_t INDEX>
    int operator()() const;
};
struct mock_aggregator
{
    template <std::size_t INDEX>
    int operator()(int const&, int const&) const;
};
struct mock_procedure
{
    template <std::size_t INDEX>
    void operator()(int const&) const;
};
struct mock_action
{
    template <std::size_t INDEX>
    void operator()() const;
};
static_assert(sti::generator<mock_generator, int>);
static_assert(sti::aggregator<mock_aggregator, int>);
static_assert(sti::procedure<mock_procedure, int>);
static_assert(sti::action<mock_action>);
template std::array<int, 10> sti::make_array<int, 10>(mock_generator const&);
template std::array<int, 10> sti::make_array_reversed<int, 10>(mock_generator const&);
template int sti::aggregate_array<int, 10>(mock_generator const&, mock_aggregator const&);
template void sti::array_for_each<int, 10>(std::array<int, 10> const&, mock_procedure const&);
template void sti::fixed_loop<10>(mock_action const&);
template void sti::fixed_loop_reversed<10>(mock_action const&);
#endif
