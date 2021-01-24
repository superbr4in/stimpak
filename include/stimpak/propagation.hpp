#pragma once

#include <memory>

#include <experimental/propagate_const>

namespace sti
{
    template <typename T>
    using shared_pptr = std::experimental::propagate_const<std::shared_ptr<T>>;
    template <typename T, typename Deleter = std::default_delete<T>>
    using unique_pptr = std::experimental::propagate_const<std::unique_ptr<T, Deleter>>;
}
