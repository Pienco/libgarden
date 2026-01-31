#pragma once

#include "types.hpp"

struct FieldRect
{
	class iterator
	{
	public:
		constexpr const Vector2i& operator*() const { return m_Position; }
		constexpr Vector2i& operator*() { return m_Position; }

		iterator& operator++();

		friend bool operator!=(const iterator& left, const iterator& right);

	private:
		const FieldRect *m_pRect;
		const Vector2i *m_pEnd;
		Vector2i m_Position;
	};
	ASSERT_SIZE(iterator, 0x10);

	iterator begin() const;
	iterator end() const;

	constexpr s32 GetWidth() const { return (max.x - min.x) + 1; }
	constexpr s32 GetHeight() const { return (max.y - min.y) + 1; }
	bool Contains(const Vector2i& pos) const;
	size_t ToIndex(const Vector2i& pos) const { return static_cast<size_t>(pos.y * GetWidth() + pos.x); }
	const auto& GetMin() const { return min; }
	const auto& GetMax() const { return max; }

	Vector2i min;
	Vector2i max;
};
ASSERT_SIZE(FieldRect, 0x10);
