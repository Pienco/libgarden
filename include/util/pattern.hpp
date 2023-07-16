#ifndef UTIL_PATTERN_HPP
#define UTIL_PATTERN_HPP

#include "types.h"
#include <utility>
#include <tuple>

namespace util
{
	namespace detail
	{
		template<typename TIndex, size_t... I>
		FORCE_INLINE constexpr void expand_pattern_impl(auto&& fn, std::index_sequence<I...>)
		{
			(fn.template operator() < (TIndex)I > (), ...);
		}

		template<typename TIndex, size_t... I>
		FORCE_INLINE constexpr auto expand_pattern_impl(auto&& fn, auto&& resultFn, std::index_sequence<I...>)
		{
			return resultFn(fn.template operator() < (TIndex)I > ()...);
		}

		template<template<typename...> typename T, size_t... I>
		FORCE_INLINE constexpr auto expand_braced_init_impl(auto&& fn, std::index_sequence<I...>)
		{
			return T { fn.template operator() < I > () ... };
		}

		template<template<typename, size_t> typename T, size_t... I>
		FORCE_INLINE constexpr auto expand_braced_init_impl(auto&& fn, std::index_sequence<I...>)
		{
			return T { fn.template operator() < I > () ... };
		}

		template<typename T, size_t... I>
		FORCE_INLINE constexpr auto expand_braced_init_impl(auto&& fn, std::index_sequence<I...>)
		{
			return T { fn.template operator() < I > () ... };
		}
	}

	template<size_t N>
	FORCE_INLINE constexpr void expand_pattern(auto&& fn)
	{
		detail::expand_pattern_impl<size_t>(std::forward<decltype(fn)>(fn), std::make_index_sequence<N>());
	}

	template<size_t N>
	FORCE_INLINE constexpr auto expand_pattern(auto&& fn, auto&& resultFn)
	{
		return detail::expand_pattern_impl<size_t>(std::forward<decltype(fn)>(fn), std::forward<decltype(resultFn)>(resultFn), std::make_index_sequence<N>());
	}

	template<template<typename, size_t> typename T, size_t N>
	FORCE_INLINE constexpr auto expand_braced_init(auto&& fn)
	{
		return detail::expand_braced_init_impl<T>(std::forward<decltype(fn)>(fn), std::make_index_sequence<N>());
	}

	template<template<typename...> typename T, size_t N>
	FORCE_INLINE constexpr auto expand_braced_init(auto&& fn)
	{
		return detail::expand_braced_init_impl<T>(std::forward<decltype(fn)>(fn), std::make_index_sequence<N>());
	}

	template<typename T, size_t N>
	FORCE_INLINE constexpr auto expand_braced_init(auto&& fn)
	{
		return detail::expand_braced_init_impl<T>(std::forward<decltype(fn)>(fn), std::make_index_sequence<N>());
	}

	template<size_t N>
	FORCE_INLINE constexpr auto expand_recursion(auto&& fn)
	{
		if constexpr (N == 0) return;
		else if constexpr (N == 1) return fn.template operator() < N - 1 > ();
		else return fn.template operator() < N - 1 > (expand_recursion(fn));
	}


	template<size_t N, auto Fn>
	FORCE_INLINE constexpr auto expand_recursion_constexpr()
	{
		if constexpr (N == 0) return;
		else if constexpr (N == 1) return Fn.template operator() < N - 1 > ();
		else return Fn.template operator() < N - 1, expand_recursion_constexpr<N - 1, Fn>() > ();
	}

	template<size_t N, auto Fn>
	FORCE_INLINE constexpr auto expand_recursion_with_feedback()
	{
		if constexpr (N == 0) return;
		else if constexpr (N == 1) return Fn.template operator() < N - 1, Fn.template operator() < N - 1 > () > ();
		else
		{
			if consteval
			{
				constexpr auto result = expand_recursion_with_feedback<N - 1, Fn>();
				return Fn.template operator() < N - 1, Fn.template operator() < N - 1 > (std::forward<decltype(result)>(result)) > (std::forward<decltype(result)>(result));
			}
			else
			{
				auto result = expand_recursion_with_feedback<N - 1, Fn>();
				return Fn.template operator() < N - 1, Fn.template operator() < N - 1 > (std::forward<decltype(result)>(result)) > (std::forward<decltype(result)>(result));
			}
		}
	}

	constexpr size_t index_of(auto&& container, auto&& value)
	{
		for (auto&& elem : container)
		{
			if (elem == value) return &elem - container.begin();
		}
		return container.end() - container.begin();
	}

	template<std::array Src, std::array Dst>
	constexpr auto map_to(auto&& value, auto&& def = { })
	{
		static_assert(Src.size() == Dst.size());
		auto index = index_of(Src, value);
		if (index == Src.size()) return def;
		else return Dst[index];
	}

	template<std::array Src, auto value, auto... Dst>
	constexpr auto map_to()
	{
		static_assert(Src.size() == sizeof...(Dst));
		constexpr auto index = index_of(Src, value);
		static_assert(index < Src.size());
		return std::get<index>(std::forward_as_tuple(Dst...));
	}

	template<std::array Dst>
	constexpr auto map_to(auto&& value)
	{
		size_t i = static_cast<size_t>(value);
		return Dst[i];
	}

	template<std::array Src, typename Dst, auto Value, typename Default = void>
	using map_to_type = std::conditional_t<index_of(Src, Value) == Src.size(),
		Default, std::tuple_element_t<index_of(Src, Value), Dst>>;


	template<std::pair... Pairs>
	constexpr auto parse_seq(auto& it, auto&& def)
	{
		std::remove_cvref_t<decltype(def)> result;
		bool found = false;
		([&it, &result, &found]<std::pair Pair>()
		{
			if (found) return;
			constexpr auto seq = std::get<0>(Pair);
			auto cur = it;
			for (auto&& e : seq)
			{
				if (*cur != e) return;
				cur++;
			}
			found = true;
			result = std::get<1>(Pair);
			it = cur;
		}.template operator() < Pairs > (), ...);
		if (!found) result = def;
		return result;
	}
}

#endif