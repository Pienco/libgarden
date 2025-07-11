#ifndef UTIL_ENUM_HPP
#define UTIL_ENUM_HPP

#include <utility>

#define DEFINE_INCREMENT_DECREMENT(E) \
constexpr E& operator++(E& v) \
{ \
	v = static_cast<E>(std::to_underlying(v) + std::underlying_type_t<E> { 1 }); \
	return v; \
} \
constexpr E operator++(E& v, int) \
{ \
	const E result = v; \
	++v; \
	return result; \
} \
constexpr E& operator--(E& v) \
{ \
	v = static_cast<E>(std::to_underlying(v) - std::underlying_type_t<E> { 1 }); \
	return v; \
} \
constexpr E operator--(E& v, int) \
{ \
	const E result = v; \
	--v; \
	return result; \
}

#endif