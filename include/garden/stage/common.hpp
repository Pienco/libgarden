#pragma once

#include "BgID.hpp"
#include "nn/math/Vector.hpp"

namespace stage
{
	using namespace math;
	using BlockPosition = math::Vector<s32, 2>;
	using Position = math::Vector<s32, 2>;
	using Size = math::Vector<s32, 2>;
	using PositionF = math::Vector3;

	constexpr float ToPositionF(s32 coordinate)
	{
		return static_cast<float>((coordinate * 32) + 16);
	}

	constexpr PositionF ToPositionF(s32 x, s32 y)
	{
		return { ToPositionF(x), 0.0f, ToPositionF(y) };
	}

	constexpr PositionF ToPositionF(Position pos)
	{
		return ToPositionF(pos.x(), pos.y());
	}

	void ToPosition(s32& x, s32& y, const PositionF& pos);

	inline Position ToPosition(const PositionF& pos)
	{
		s32 x, y;
		ToPosition(x, y, pos);
		return {x, y};
	}

	inline Vector2u8 ToPosition8(const PositionF& pos)
	{
		s32 x, y;
		ToPosition(x, y, pos);
		return {static_cast<u8>(x), static_cast<u8>(y)};
	}

	struct Rect
	{
		class iterator
		{
		public:

			constexpr const Position& operator*() const { return m_Position; }
			constexpr Position& operator*() { return m_Position; }

			iterator& operator++();

			friend bool operator!=(const iterator& left, const iterator& right);

		private:
			const Rect* m_pRect;
			const Position* m_pEnd;
			Position m_Position;
		};
		ASSERT_SIZE(iterator, 0x10);

		iterator begin() const;
		iterator end() const;

		constexpr s32 GetWidth() const { return (max[0] - min[0]) + 1; }
		constexpr s32 GetHeight() const { return (max[1] - min[1]) + 1; }
		bool Contains(const Position& pos) const;
		size_t ToIndex(const Position& pos) const { return static_cast<size_t>(pos[1] * GetWidth() + pos[0]); }

		Size min;
		Size max;
	};
	ASSERT_SIZE(Rect, 0x10);

	consteval Size GetBlockSize() { return { 16, 16 }; }
	consteval Size GetTownFieldSize() { return { 5, 4 }; }
	consteval size_t GetTownItemBlockCount()
	{
		constexpr auto size = GetTownFieldSize();
		return size.x() * size.y();
	}

	const char* GetBgModelName();
}
