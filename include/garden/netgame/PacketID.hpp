#pragma once

#include <nn/types.h>

namespace netgame
{
	enum class PacketID : u8
	{
		PLAYER_0_ACTION = 0x33,
		PLAYER_1_ACTION = 0x34,
		PLAYER_2_ACTION = 0x35,
		PLAYER_3_ACTION = 0x36,
		ITEM_PLACEMENT = 0x3a,
		INSECT_UPDATE = 0x3b,
		FISH_UPDATE = 0x3c,
	};
};
