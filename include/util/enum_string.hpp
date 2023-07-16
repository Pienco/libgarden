#ifndef UTIL_ENUM_STRING_HPP
#define UTIL_ENUM_STRING_HPP

#include "util/string.hpp"

namespace util
{
	template<auto V, Character C = char, bool SkipScopeNames = true>
	consteval auto enum_to_name()
	{
		auto str = replace_all<value_string<V, C, SkipScopeNames>(), convert<C>("_"_a), convert<C>(" "_a)>();
		std::transform(str.begin(), str.end(), str.begin(), [](C c) -> C
		{
			return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
		});
		return str;
	}
}
#endif
