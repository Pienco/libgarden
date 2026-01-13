#pragma once

#include <nn/types.h>

namespace netgame
{

	enum class StatePacketID : u8
	{
		NONE = 0x00,
		PLAYER_0 = 0x01,
		PLAYER_1 = 0x02,
		PLAYER_2 = 0x03,
		PLAYER_3 = 0x04,
		PLAYER_0_ACTION = 0x05,
		PLAYER_1_ACTION = 0x06,
		PLAYER_2_ACTION = 0x07,
		PLAYER_3_ACTION = 0x08,
		NPC_BEGIN = 0x09,
		NPC_0 = 0x09,
		NPC_1 = 0x0a,
		NPC_2 = 0x0b,
		NPC_3 = 0x0c,
		NPC_4 = 0x0d,
		NPC_5 = 0x0e,
		NPC_6 = 0x0f,
		NPC_7 = 0x10,
		NPC_8 = 0x11,
		NPC_9 = 0x12,
		NPC_10 = 0x13,
		NPC_11 = 0x14,
		NPC_12 = 0x15,
		NPC_13 = 0x16,
		NPC_63 = 0x47,
		NPC_END = 0x48,
		INSECT_BEGIN = 0x48,
		INSECT_0 = 0x48,
		INSECT_1 = 0x49,
		INSECT_2 = 0x4a,
		INSECT_3 = 0x4b,
		INSECT_4 = 0x4c,
		INSECT_5 = 0x4d,
		INSECT_6 = 0x4e,
		INSECT_7 = 0x4f,
		INSECT_8 = 0x50,
		INSECT_9 = 0x51,
		INSECT_10 = 0x52,
		INSECT_11 = 0x53,
		INSECT_END = 0x54,
		FISH_BEGIN = 0x54,
		FISH_0 = 0x54,
		FISH_1 = 0x55,
		FISH_2 = 0x56,
		FISH_3 = 0x57,
		FISH_4 = 0x58,
		FISH_5 = 0x59,
		FISH_6 = 0x5a,
		FISH_7 = 0x5b,
		FISH_END = 0x5c,
		COCKROACH_0 = 0x5c,
		COCKROACH_1 = 0x5d,

		COUNT = 0x96,
	};

};
