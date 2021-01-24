#pragma once

#include <ranges>

namespace sti
{
    template <std::ranges::range Map>
    std::pair<typename Map::key_type, typename Map::mapped_type> map_extract(Map* map, std::ranges::iterator_t<Map> const& position)
    {
        auto const node = map->extract(position);
        return std::pair(std::move(node.key()), std::move(node.mapped()));
    }
    template <std::ranges::range Set>
    typename Set::value_type set_extract(Set* set, std::ranges::iterator_t<Set> const& position)
    {
        return std::move(set->extract(position).value());
    }
}
