#pragma once

#include "netgame/PlayerNo.hpp"
#include "item/fish.hpp"
#include "math/Vector.hpp"

namespace netgame
{

	struct PACKED FishState
	{
		static constexpr u32 positionScale = 4;

		item::FishID id : 7;
		u8 state : 4;
		u16 posX : 10;
		u16 posZ : 10;
		PlayerNo owner : 3;
		u8 flags;
	};
	ASSERT_SIZE(FishState, 0x6);

}
