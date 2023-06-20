#ifndef UTIL_PATTERN_HPP
#define UTIL_PATTERN_HPP

#include "types.h"
#include <utility>

template<typename TIndex, size_t... I>
FORCE_INLINE constexpr void expand_pattern_impl(auto&& fn, std::index_sequence<I...>)
{
	(fn.template operator() < (TIndex)I > (), ...);
}

template<template<typename...> typename T, size_t... I>
FORCE_INLINE consteval auto expand_braced_init_impl(auto&& fn, std::index_sequence<I...>)
{
	return T { fn.template operator() < I > () ... };
}

template<template<typename, size_t> typename T, size_t... I>
FORCE_INLINE consteval auto expand_braced_init_impl(auto&& fn, std::index_sequence<I...>)
{
	return T { fn.template operator() < I > () ... };
}

template<size_t N>
FORCE_INLINE constexpr void expand_pattern(auto&& fn)
{
	expand_pattern_impl<size_t>(std::forward<decltype(fn)>(fn), std::make_index_sequence<N>());
}

template<template<typename, size_t> typename T, size_t N>
FORCE_INLINE consteval auto expand_braced_init(auto&& fn)
{
	return expand_braced_init_impl<T>(std::forward<decltype(fn)>(fn), std::make_index_sequence<N>());
}

template<template<typename...> typename T, size_t N>
FORCE_INLINE consteval auto expand_braced_init(auto&& fn)
{
	return expand_braced_init_impl<T>(std::forward<decltype(fn)>(fn), std::make_index_sequence<N>());
}

template<typename TIndex, size_t N>
FORCE_INLINE constexpr void expand_pattern(auto&& fn)
{
	expand_pattern_impl<TIndex>(std::forward<decltype(fn)>(fn), std::make_index_sequence<N>());
}

#endif
