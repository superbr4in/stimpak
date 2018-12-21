#pragma once

#include <type_traits>

namespace sti
{
    /*!
     *  Implements SFINAE behaviour by compensating a substitution failure with the
     *  respective identity function.
     */
    template <typename T, typename TFunc, typename = void>
    struct sfiid
    {
    private:

        T& value_;

    public:

        inline sfiid(TFunc&, T& value)
            : value_(value) { }

        inline auto operator()() const
        {
            return value_;
        }
    };
    template <typename T, typename TFunc>
    struct sfiid<T, TFunc, std::void_t<decltype(std::declval<TFunc>()(std::declval<T>()))>>
    {
    private:

        TFunc& func_;
        T& value_;

    public:

        inline sfiid(TFunc& func, T& value)
            : func_(func), value_(value) { }

        inline auto operator()() const
        {
            return func_(value_);
        }
    };
}
