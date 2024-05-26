#ifndef MAP_COMMON_HPP
#define MAP_COMMON_HPP

#include "math/Vector.hpp"
#include "map/BgID.hpp"

namespace map
{
	using ChunkPosition = math::Vector2i;
	using Position = math::Vector2i;
	using Size = math::Vector2i;

	struct Rect
	{
		Size start;
		Size end;
	};
	ASSERT_SIZE(Rect, 0x10);

	consteval Size GetChunkSize() { return { 16, 16 }; }
	consteval Size GetTownFieldSize() { return { 5, 4 }; }
	consteval size_t GetTownItemChunkCount()
	{
		constexpr auto size = GetTownFieldSize();
		return size.x() * size.y();
	}

	const char* GetBgModelName();
}

#endif
