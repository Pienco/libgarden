#pragma once

#include "PlayerNo.hpp"
#include "../item/insect.hpp"
#include "nn/math/Vector.hpp"

namespace netgame
{

	struct PACKED InsectState
	{
		static constexpr u32 positionScale = 4;

		item::InsectID id : 7;
		u8 state : 4;
		u16 posX : 10;
		u16 posZ : 10;
		PlayerNo owner : 3;
		u8 flags;
	};
	ASSERT_SIZE(InsectState, 0x6);

}
