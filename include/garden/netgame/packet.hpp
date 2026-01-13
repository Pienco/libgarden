#pragma once

#include "../item/Item.hpp"
#include "../stage/Name.hpp"
#include "nn/math/Vector.hpp"

namespace netgame
{

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"

	struct PACKED ShowPacket
	{
		static constexpr u32 positionScale = 4;

		constexpr ShowPacket() = default;
		constexpr ShowPacket(const item::Item& item, const math::Vector3& pos) :
			cmd {1},
			id {item.ToInsectFishID()},
			x {static_cast<u32>(pos[0]) / positionScale},
			z {static_cast<u32>(pos[2]) / positionScale} { }

		u8 cmd : 2 {};
		u32 id : 7 {};
		u32 x : 10 {};
		u32 z : 10 {};
	};
	ASSERT_SIZE(ShowPacket, 4);

#pragma GCC diagnostic pop

}
