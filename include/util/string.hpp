#ifndef UTIL_STRING_HPP
#define UTIL_STRING_HPP

#include <algorithm>
#include <array>
#include <cstddef>
#include <concepts>
#include <string>

#include "util/common.hpp"
#include "util/pattern.hpp"

namespace util
{
	template<typename T>
	concept Character = std::same_as<T, char> || std::same_as<T, wchar_t>
		|| std::same_as<T, char8_t> || std::same_as<T, char16_t> || std::same_as<T, char32_t>;

	template<typename T>
	concept Array = std::same_as<std::decay_t<T>, std::array<typename std::decay_t<T>::value_type, std::tuple_size_v<std::decay_t<T>>>>;

	namespace detail
	{
		template<Character T, size_t N>
		struct CharacterArrayWrapper
		{
			consteval CharacterArrayWrapper(const T(&s)[N]): array(std::to_array(s))
			{
			}

			std::array<T, N> array;
		};

		template<Character T, size_t N>
		struct CharacterArrayWrapperNoTerminator
		{
			consteval CharacterArrayWrapperNoTerminator(const T(&s)[N])
			{
				std::copy(s, s + N - 1, array.begin());
			}

			std::array<T, N - 1> array;
		};

		template<Character T>
		inline constexpr auto TERMINATOR = static_cast<T>(0);

		template<Character T>
		inline constexpr auto EMPTY_STRING = std::array<T, 1> { TERMINATOR<T> };
	}



	template<Character T, size_t N>
	constexpr size_t length_of(std::array<T, N>&& str)
	{
		size_t result = 0;
		while (str[result] != detail::TERMINATOR<T>) result++;
		return result;
	}

	template<Character T, size_t N>
	constexpr size_t length_of(const std::array<T, N>& str)
	{
		size_t result = 0;
		while (str[result] != detail::TERMINATOR<T>) result++;
		return result;
	}
}

template<util::Array L, util::Array R>
consteval auto operator+(L&& left, R&& right) requires (std::is_same_v<typename std::decay_t<L>::value_type, typename std::decay_t<R>::value_type>)
{
	constexpr auto n = std::tuple_size_v<std::decay_t<L>>;
	constexpr auto m = std::tuple_size_v<std::decay_t<R>>;
	if constexpr (n == 0) return right;
	else if constexpr (m == 0) return left;
	else
	{
		std::array<typename std::decay_t<L>::value_type, n + m - 1> arr {};
		for (size_t i = 0; i < n - 1; i++)
			arr[i] = left[i];
		for (size_t i = 0; i < m; i++)
			arr[i + util::length_of(left)] = right[i];
		return arr;
	}
}

namespace util
{
	constexpr size_t find(auto&& str, auto&& sub, size_t pos = 0)
	{
		return std::search(str.cbegin() + pos, str.cend(), sub.cbegin(), sub.cend() - 1) - str.cbegin();
	}

	constexpr size_t find_skip(auto&& str, auto&& sub, size_t pos = 0)
	{
		auto p = find(std::forward<decltype(str)>(str), std::forward<decltype(sub)>(sub), pos);
		if (p != str.size()) p += sub.size() - 1;
		return p;
	}

	template<Character C, template<typename, size_t> typename Template, Character T, size_t N>
	constexpr auto convert(Template<T, N>&& str)
	{
		std::array<C, N> result;
		std::copy(str.cbegin(), str.cend(), result.begin());
		return result;
	}

	template<size_t Num, template<typename, size_t> typename Template, typename T, size_t N, size_t M>
	consteval auto replace(Template<T, N> Str, Template<T, M> With, size_t Pos)
	{
		constexpr auto S = With.size() - 1;
		Template<T, Str.size() - Num + S> result {};
		size_t i = 0;
		for (; i < Pos; i++) result[i] = Str[i];
		for (i = Pos; i < S + Pos; i++) result[i] = With[i - Pos];
		for (i = Pos; i + Num < Str.size(); i++) result[i + S] = Str[i + Num];
		return result;
	}

	template<typename T, size_t N, size_t M>
	consteval auto replace(std::array<T, N> Str, std::array<T, M> With, size_t pos)
	{
		return replace<With.size() - 1>(Str, With, pos);
	}

	template<std::array Str, size_t Start, size_t Count>
	consteval auto substr()
	{
		using T = typename decltype(Str)::value_type;
		std::array<T, Count + 1> result;
		std::copy(Str.begin() + Start, Str.begin() + Start + Count, result.begin());
		result[result.size() - 1] = detail::TERMINATOR<T>;
		return result;
	}

	template<template<typename, size_t> typename Template, Template Str, Template What, Template With>
	consteval auto replace_all()
	{
		using T = typename decltype(Str)::value_type;
		return expand_recursion_constexpr < 2, [&]<size_t I, auto In = 0>()
		{
			std::basic_string<T> s(Str.cbegin(), Str.cend());
			std::basic_string<T> what(What.cbegin(), What.cend() - 1);
			std::basic_string<T> with(With.cbegin(), With.cend() - 1);
			for (typename std::basic_string<T>::size_type pos {};
				s.npos != (pos = s.find(what.data(), pos, what.length()));
				pos += with.length())
			{
				s.replace(pos, what.length(), with.data(), with.length());
			}
			if constexpr (I != 0)
			{
				Template<T, In> out {};
				std::copy(s.begin(), s.end(), out.begin());
				return out;
			}
			else return s.length();
		} > ();
	}

	template<std::array Str, std::array What, std::array With>
	consteval auto replace_all()
	{
		return replace_all<std::array, Str, What, With>();
	}
}

template<util::detail::CharacterArrayWrapperNoTerminator W>
consteval auto operator""_r()
{
	return W.array;
}

template<util::detail::CharacterArrayWrapper W>
consteval auto operator""_a()
{
	return W.array;
}

namespace util
{
	template<auto V, Character C = char, bool SkipScopeNames = true>
	consteval auto value_string()
	{
		constexpr std::array func = convert<C>(std::to_array(__PRETTY_FUNCTION__));
		constexpr auto find_end = convert<C>(";"_a);
		constexpr auto end_pos = find(func, find_end);
		constexpr auto begin_pos = [&]
		{
			constexpr auto find_begin = convert<C>("V = "_a);
			constexpr auto res = convert<C>("::"_a);
			auto result = find_skip(func, find_begin);
			if constexpr (SkipScopeNames)
			{
				for (size_t pos = find_skip(func, res, result); pos != func.size() && pos < end_pos; pos = find_skip(func, res, result))
				{
					result = pos;
				}
			}
			return result;
		}();

		return substr<func, begin_pos, end_pos - begin_pos>();
	}
}
#endif