#ifndef UTIL_TUPLE_HPP
#define UTIL_TUPLE_HPP

#include "types.h"
#include <type_traits>


namespace detail
{
	template <typename Tuple, typename... Ts>
	struct PACKED TupleRec { };

	template <typename Tuple, typename T>
	struct PACKED TupleRec<Tuple, T>
	{
		constexpr TupleRec() = default;
		constexpr TupleRec(const T& t): element(t) { };

		template<size_t Index>
		consteval auto At() const
		{
			static_assert(Index == Tuple::GetElementCount() - 1);
			return element;
		}

		constexpr const auto& operator[](s32 index) const
		{
			return element;
		}

		T element;
	};

	template <typename Tuple, typename T, typename... Ts>
	struct PACKED TupleRec<Tuple, T, Ts...>
	{
		constexpr TupleRec() = default;
		constexpr TupleRec(const T& t, const Ts&... ts): element(t), rest(ts...) { };

		static consteval size_t GetCurrentIndex()
		{
			return Tuple::GetElementCount() - (sizeof...(Ts) + 1);
		}

		template<size_t Index>
		consteval auto At() const
		{
			if constexpr (GetCurrentIndex() == Index) return element;
			else return rest.template At<Index>();
		}

		constexpr const auto& operator[](s32 index) const
		{
			if (GetCurrentIndex() == index) return element;
			else return rest.template operator[](index);
		}

		T element;
		TupleRec<Tuple, Ts...> rest;
	};
}

template<typename T>
concept TupleType =
!std::is_reference_v<T>
&& std::is_standard_layout_v<T>;
// && !std::is_pointer_v<T>;

template<TupleType T, TupleType... Ts>
struct PACKED Tuple
{
	static consteval size_t GetElementCount() { return 1 + sizeof...(Ts); }

	constexpr Tuple() = default;
	constexpr Tuple(const T& t, const Ts&... ts): impl(t, ts...) { };

	template<size_t Index>
	consteval auto At() const
	{
		static_assert(Index < GetElementCount());
		return impl.template At<Index>();
	}

	constexpr const auto& operator[](s32 index) const
	{
		return impl.template operator[](index);
	}

	detail::TupleRec<Tuple, T, Ts...> impl;
};



#endif
