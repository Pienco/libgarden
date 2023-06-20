#ifndef UTIL_LOOKUP_HPP
#define UTIL_LOOKUP_HPP

#include "util/common.hpp"

#include <algorithm>
#include <array>
#include <concepts>
#include <cstddef>

namespace util
{
	template<std::array Positions, std::array Luts>
		requires (Positions.size() > 0 && std::is_sorted(Positions.begin(), Positions.end()) && Luts.size() == Positions.size())
	struct LookupHelper
	{
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wreturn-type"
		static constexpr const auto& operator[](auto pos)
		{
			constexpr auto& positions = make_static<Positions>;
			constexpr auto& luts = make_static<Luts>;
			for (size_t i = 0; i < positions.size(); i++)
			{
				const size_t index = positions.size() - 1 - i;
				const auto p = positions[index];
				if (pos >= p)
				{
					if constexpr (requires { luts[index]->operator[](static_cast<size_t>(pos) - static_cast<size_t>(p)); })
						return luts[index]->operator[](static_cast<size_t>(pos) - static_cast<size_t>(p));
					else return luts[index][static_cast<size_t>(pos) - static_cast<size_t>(p)];
				}
			}
		}
	#pragma GCC diagnostic pop
	};

	namespace detail
	{
		template<std::array Luts>
		constexpr auto LutElementType()
		{
			if constexpr (requires { Luts[0]->operator[](0); })
				return Luts[0]->operator[](0);
			else return Luts[0][0];
		}
	}

	template<std::array Positions, std::array Luts, decltype(detail::LutElementType<Luts>()) Default = decltype(detail::LutElementType<Luts>()) { } >
		requires (Positions.size() > 0 && std::is_sorted(Positions.begin(), Positions.end()) && Luts.size() == Positions.size() / 2
	&& Positions.size() % 2 == 0 && []
	{
		bool result = true;
		for (size_t i = 0; i < Positions.size(); i += 2)
		{
			if (Positions[i] > Positions[i + 1])
				result = false;
		}
		return result;
	}())
		struct LookupHelperBounded
	{
		static constexpr auto operator[](auto pos)
		{
			constexpr auto& positions = make_static<Positions>;
			constexpr auto& luts = make_static<Luts>;
			for (size_t i = 0; i < luts.size(); i++)
			{
				const auto begin = positions[i * 2];
				const auto end = positions[i * 2 + 1];
				if (pos < begin) return Default;
				if (pos < end)
				{
					if constexpr (requires { luts[i]->operator[](static_cast<size_t>(pos) - static_cast<size_t>(begin)); })
						return luts[i]->operator[](static_cast<size_t>(pos) - static_cast<size_t>(begin));
					else return luts[i][static_cast<size_t>(pos) - static_cast<size_t>(begin)];
				}
			}
			return Default;
		}
	};
}

#endif