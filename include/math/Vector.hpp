#ifndef MATH_VECTOR_HPP
#define MATH_VECTOR_HPP

#include "util/pattern.hpp"

template<typename T, u32 Dim>
struct Vector
{

};

template<typename T>
struct Vector<T, 1>
{
	using Self = Vector<T, 1>;

	constexpr T& operator[](int i)
	{
		return (&x)[i];
	}
	constexpr const T& operator[](int i) const
	{
		return (&x)[i];
	}

	constexpr void Clamp(Self max)
	{
		clamp(x, max.x);
	}

	friend constexpr Self operator+(Self left, Self right)
	{
		return { left.x + right.x };
	}
	friend constexpr Self operator-(Self left, Self right)
	{
		return { left.x - right.x };
	}
	friend constexpr Self operator*(Self left, T right)
	{
		return { left.x * right };
	}
	friend constexpr Self operator*(T left, Self right)
	{
		return { left * right.x };
	}

	T x;

protected:

	template<typename Vec>
	static constexpr void VecOp(auto&& fn)
	{
		expand_pattern<GetDim<Vec>()>(std::forward<decltype(fn)>(fn));
	}

private:

	template<typename Vec>
	static consteval size_t GetDim()
	{
		if constexpr (!requires { Vec::x; }) return 0;
		if constexpr (!requires { Vec::y; }) return 1;
		if constexpr (!requires { Vec::z; }) return 2;
		if constexpr (!requires { Vec::w; }) return 3;
		if constexpr (requires { Vec::w; }) return 4;
	}

	template<size_t Index, typename Vec>
	friend constexpr T& At(Vec& self)
	{
		static_assert(Index < GetDim<Vec>());
		static_assert(requires { Vec::x; });

		if constexpr (Index == 0) return self.x;
		if constexpr (Index == 1) return self.y;
		if constexpr (Index == 2) return self.z;
		if constexpr (Index == 3) return self.w;
	}
};
template<typename T>
struct Vector<T, 2>: Vector<T, 1>
{
	using Self = Vector<T, 2>;

	constexpr void Clamp(Self max)
	{
		Vector<T, 1>::Clamp({ max.x });
		clamp(y, max.y);
	}

	friend constexpr Self operator+(Self left, Self right)
	{
		return { left.x + right.x, left.y + right.y };
	}
	friend constexpr Self& operator+=(Self& left, Self right)
	{
		left.x += right.x;
		left.y += right.y;
		return left;
	}
	friend constexpr Self operator-(Self left, Self right)
	{
		return { left.x - right.x, left.y - right.y };
	}
	friend constexpr Self operator*(Self left, Self right)
	{
		return { left.x * right.x, left.y * right.y };
	}
	friend constexpr Self operator*(Self left, T right)
	{
		return { left.x * right, left.y * right };
	}
	friend constexpr Self operator*(T left, Self right)
	{
		return right * left;
	}
	friend constexpr bool operator<(Self left, Self right)
	{
		return left.x < right.x&& left.y < right.y;
	}
	friend constexpr bool operator>(Self left, Self right)
	{
		return left.x > right.x && left.y > right.y;
	}
	friend constexpr bool operator>=(Self left, Self right)
	{
		return left.x >= right.x && left.y >= right.y;
	}
	friend constexpr bool operator==(Self left, Self right) = default;

	T y;
};

template<typename T>
struct Vector<T, 3>: Vector<T, 2>
{
	T z;
};
template<typename T>
struct Vector<T, 4>: Vector<T, 3>
{
	T w;
};

typedef Vector<s32, 2> Vector2i;
typedef Vector<s32, 3> Vector3i;
typedef Vector<float, 2> Vector2;
typedef Vector<float, 3> Vector3;
typedef Vector<float, 4> Vector4;

ASSERT_SIZE(Vector3, 0xc);
ASSERT_SIZE(Vector4, 0x10);

template<typename T, u32 Rows, u32 Columns>
struct Matrix
{
	Vector<T, Columns> rows[Rows];
};

typedef Matrix<float, 4, 4> Matrix4;
typedef Matrix<float, 3, 4> Matrix34;

ASSERT_SIZE(Matrix4, 0x40);
ASSERT_SIZE(Matrix34, 0x30);

#endif
