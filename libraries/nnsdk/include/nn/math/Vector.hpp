#pragma once

#include <nn/types.h>
#include <gardenex/util/pattern.hpp>

#include <array>
#include <cmath>

namespace math
{
	template<typename T, size_t N>
	struct Vector
	{
		using Self = Vector<T, N>;
		using ValueType = T;

		static consteval auto Dim()
		{
			return N;
		}

		template<size_t I>
		FORCE_INLINE constexpr T& get()
		{
			return std::get<I>(elements);
		}

		template<size_t I>
		FORCE_INLINE constexpr const T& get() const
		{
			return std::get<I>(elements);
		}

		FORCE_INLINE constexpr T& operator[](size_t i)
		{
			return elements[i];
		}

		FORCE_INLINE constexpr const T& operator[](size_t i) const
		{
			return elements[i];
		}

		FORCE_INLINE constexpr T& at(size_t i)
		{
			return elements[i];
		}

		FORCE_INLINE constexpr const T& at(size_t i) const
		{
			return elements[i];
		}

		FORCE_INLINE constexpr T& x() requires (N >= 1)
		{
			return get<0>();
		}
		FORCE_INLINE constexpr T x() const requires (N >= 1)
		{
			return get<0>();
		}
		FORCE_INLINE constexpr T& y() requires (N >= 2)
		{
			return get<1>();
		}
		FORCE_INLINE constexpr T y() const requires (N >= 2)
		{
			return get<1>();
		}
		FORCE_INLINE constexpr T& z() requires (N >= 3)
		{
			return get<2>();
		}
		FORCE_INLINE constexpr T z() const requires (N >= 3)
		{
			return get<2>();
		}
		FORCE_INLINE constexpr T& w() requires (N >= 4)
		{
			return get<3>();
		}
		FORCE_INLINE constexpr T w() const requires (N >= 4)
		{
			return get<3>();
		}

		template<std::common_with<Self> S>
		FORCE_INLINE constexpr void Clamp(S&& max)
		{
			Operation([this, max]<size_t I> FORCE_INLINE
				{
					if (this->get<I>() > max.template get<I>())
						this->get<I>() = max.template get<I>();
				});
		}

		template<std::common_with<Self> S>
		FORCE_INLINE constexpr T Dot(S&& right) const
		{
			return Operation([this, right]<size_t I> FORCE_INLINE
				{
					return this->get<I>() * right.template get<I>();
				},
				[] FORCE_INLINE(auto&&... results)
			{
				return (... + results);
			});
		}

		FORCE_INLINE constexpr T LengthSquared() const
		{
			return Dot(*this);
		}

		FORCE_INLINE constexpr T Length() const
		{
			return std::sqrt(LengthSquared());
		}

		template<std::common_with<Self> S1, std::common_with<Self> S2>
		FORCE_INLINE friend constexpr Self operator+(S1&& left, S2&& right)
		{
			return ArithmeticOperation([] FORCE_INLINE(auto l, auto r)
			{
				return l + r;
			}, std::forward<S1>(left), std::forward<S2>(right));
		}

		template<std::common_with<Self> S>
		FORCE_INLINE constexpr Self& operator+=(S&& right)
		{
			Operation([this, right]<size_t I> FORCE_INLINE
				{
					this->get<I>() += right.template get<I>();
				});
			return *this;
		}

		template<std::common_with<Self> S1, std::common_with<Self> S2>
		FORCE_INLINE friend constexpr Self operator-(S1&& left, S2&& right)
		{
			return ArithmeticOperation([] FORCE_INLINE(auto l, auto r)
			{
				return l - r;
			}, std::forward<S1>(left), std::forward<S2>(right));
		}

		template<std::common_with<Self> S>
		FORCE_INLINE constexpr Self& operator-=(S&& right)
		{
			Operation([this, right]<size_t I> FORCE_INLINE
				{
					this->get<I>() -= right.template get<I>();
				});
			return *this;
		}

		template<std::common_with<Self> S>
		FORCE_INLINE friend constexpr Self operator*(S&& left, T&& right)
		{
			return ArithmeticOperation([] FORCE_INLINE(auto l, auto r)
			{
				return l * r;
			}, std::forward<S>(left), std::forward<T>(right));
		}

		template<std::common_with<Self> S>
		FORCE_INLINE friend constexpr Self operator*(T&& left, S&& right)
		{
			return operator*(std::forward<S>(right), std::forward<T>(left));
		}

		FORCE_INLINE constexpr Self& operator*=(T&& right)
		{
			Operation([this, right]<size_t I> FORCE_INLINE
				{
					this->get<I>() *= right;
				});
			return *this;
		}

		template<std::common_with<Self> S>
		FORCE_INLINE friend constexpr Self operator/(S&& left, T&& right)
		{
			return ArithmeticOperation([] FORCE_INLINE(auto l, auto r)
			{
				return l / r;
			}, std::forward<S>(left), std::forward<T>(right));
		}

		template<std::common_with<Self> S>
		FORCE_INLINE friend constexpr Self operator/(T&& left, S&& right)
		{
			return operator/(std::forward<S>(right), std::forward<T>(left));
		}

		FORCE_INLINE constexpr Self& operator/=(T&& right)
		{
			Operation([this, right]<size_t I> FORCE_INLINE
				{
					this->get<I>() /= right;
				});
			return *this;
		}

		template<std::common_with<Self> S1, std::common_with<Self> S2>
		FORCE_INLINE friend constexpr auto operator==(S1&& left, S2&& right)
		{
			return left.elements == right.elements;
		}

		std::array<T, N> elements;

	private:

		template<typename F, typename R>
		FORCE_INLINE static constexpr auto Operation(F&& fn, R&& combine)
		{
			return util::for_index_sequence<N>(std::forward<F>(fn), std::forward<R>(combine));
		}

		template<typename F>
		FORCE_INLINE static constexpr void Operation(F&& fn)
		{
			util::for_index_sequence<N>(std::forward<F>(fn));
		}

		template<typename F, typename L, typename R>
		FORCE_INLINE static constexpr auto ArithmeticOperation(F&& fn, L&& left, R&& right)
		{
			return util::create<Self, N>([&]<size_t I> FORCE_INLINE
				{
					if constexpr (std::is_convertible_v<L, Self> && std::is_convertible_v<R, Self>)
						return fn(left.template get<I>(), right.template get<I>());
					else if constexpr (std::is_convertible_v<L, Self>)
						return fn(left.template get<I>(), std::forward<R>(right));
					else if constexpr (std::is_convertible_v<R, Self>)
						return fn(std::forward<L>(left), right.template get<I>());
				});
		}

	};

	template<typename T, typename... U>
	Vector(T, U...) -> Vector<T, 1 + sizeof...(U)>;

	using Vector2s8 = Vector<s8, 2>;
	using Vector2u8 = Vector<u8, 2>;
	using Vector2s16 = Vector<s16, 2>;
	using Vector3s16 = Vector<s16, 3>;
	using Vector2u16 = Vector<u16, 2>;
	using Vector2u32 = Vector<u32, 2>;
	using Vector2i = Vector<int, 2>;
	using Vector3i = Vector<int, 3>;
	using Vector2 = Vector<float, 2>;
	using Vector3 = Vector<float, 3>;
	using Vector4 = Vector<float, 4>;

	static_assert(sizeof(Vector3) == 3 * sizeof(float));
	static_assert(sizeof(Vector4) == 4 * sizeof(float));

	template<typename T, size_t M, size_t N>
	struct Matrix
	{
		using Self = Matrix<T, M, N>;
		using Row = Vector<T, N>;
		using Column = Vector<T, M>;

		static consteval size_t Width()
		{
			return N;
		}

		static consteval size_t Height()
		{
			return M;
		}

		template<size_t I> requires (I < M)
			FORCE_INLINE constexpr Row& get()
		{
			return std::get<I>(rows);
		}

		template<size_t I> requires (I < M)
			FORCE_INLINE constexpr const Row& get() const
		{
			return std::get<I>(rows);
		}

		template<size_t I, size_t J> requires (I < M&& J < N)
			FORCE_INLINE constexpr T& get()
		{
			return get<I>().template get<J>();
		}

		template<size_t I, size_t J> requires (I < M&& J < N)
			FORCE_INLINE constexpr const T& get() const
		{
			return get<I>().template get<J>();
		}

		template<size_t I> requires (I < N)
			FORCE_INLINE constexpr Column column() const
		{
			return util::create<Vector<T, M>, M>([&]<size_t J> FORCE_INLINE
				{
					return get<J, I>();
				});
		}

		FORCE_INLINE constexpr T Trace() const
		{
			return Operation([this]<size_t I> FORCE_INLINE
				{
					return this->get<I, I>();
				},
				[](auto&&... results) FORCE_INLINE
				{
					return (... + results);
				});
		}

		FORCE_INLINE constexpr Matrix<T, N, M> Transpose() const
		{
			return util::create<Matrix<T, N, M>, N>([&]<size_t I> FORCE_INLINE
				{
					return util::create<Vector<T, M>, M>([&]<size_t J> FORCE_INLINE
					{
						return get<J, I>();
					});
				});
		}

		template<std::common_with<Self> L, std::common_with<Row> R>
		FORCE_INLINE friend constexpr Column operator*(L&& left, R&& right)
		{
			return ArithmeticOperation<Column, M>([] FORCE_INLINE(auto l, auto r)
			{
				return l.Dot(r);
			}, std::forward<L>(left), std::forward<R>(right));
		}

		std::array<Vector<T, N>, M> rows;

	private:

		template<typename F, typename R>
		FORCE_INLINE static constexpr auto Operation(F&& fn, R&& combine)
		{
			return util::for_index_sequence<N>(std::forward<F>(fn), std::forward<R>(combine));
		}

		template<typename F>
		FORCE_INLINE static constexpr void Operation(F&& fn)
		{
			util::for_index_sequence<N>(std::forward<F>(fn));
		}

		template<typename Ret, size_t RetSize, typename L, typename R>
		FORCE_INLINE static constexpr auto ArithmeticOperation(auto&& fn, L&& left, R&& right)
		{
			return util::create<Ret, RetSize>([&]<size_t I> FORCE_INLINE
				{
					if constexpr (std::is_convertible_v<L, Self> && std::is_convertible_v<R, Row>)
						return fn(left.template get<I>(), std::forward<R>(right));
					else return fn(std::forward<L>(left), right.template column<I>());
				});
		}
	};

	template<typename T, size_t N, std::same_as<Vector<T, N>>... U>
	Matrix(Vector<T, N>, U...) -> Matrix<T, 1 + sizeof...(U), N>;

	using Matrix2 = Matrix<float, 2, 2>;
	using Matrix3 = Matrix<float, 3, 3>;
	using Matrix34 = Matrix<float, 3, 4>;
	using Matrix4 = Matrix<float, 4, 4>;
}

using namespace math;
