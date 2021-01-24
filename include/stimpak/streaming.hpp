#pragma once

#include <istream>
#include <vector>

namespace sti
{
    template <std::integral CharT>
    bool begins_with(std::basic_istream<CharT>& stream, std::basic_string<CharT> const& string)
    {
        std::basic_string peeked_string(string.size(), CharT{0});

        auto const size = static_cast<std::streamsize>(peeked_string.size());
        stream.read(peeked_string.data(), size);
        stream.seekg(-size, std::ios::cur);

        return peeked_string == string;
    }

    template <std::integral T, std::integral CharT>
    T extract(std::basic_istream<CharT>& stream)
    {
        T value;
        stream.read(reinterpret_cast<CharT*>(&value), // NOLINT [cppcoreguidelines-pro-type-reinterpret-cast]
            sizeof value);

        return value;
    }
    template <std::integral T, std::integral CharT>
    std::vector<T> extract(std::basic_istream<CharT>& stream, std::size_t const& size)
    {
        std::vector<T> data(size);
        stream.read(reinterpret_cast<CharT*>(data.data()), // NOLINT [cppcoreguidelines-pro-type-reinterpret-cast]
            static_cast<std::streamoff>(data.size() * sizeof(T) / sizeof(CharT)));

        return data;
    }
}

#ifdef LINT
template bool sti::begins_with(std::istream&, std::string const&);
template bool sti::begins_with(std::wistream&, std::wstring const&);
template int sti::extract(std::istream&);
template int sti::extract(std::wistream&);
template short sti::extract(std::istream&);
template short sti::extract(std::wistream&);
template std::vector<int> sti::extract(std::istream&, std::size_t const&);
template std::vector<int> sti::extract(std::wistream&, std::size_t const&);
template std::vector<short> sti::extract(std::istream&, std::size_t const&);
template std::vector<short> sti::extract(std::wistream&, std::size_t const&);
#endif
