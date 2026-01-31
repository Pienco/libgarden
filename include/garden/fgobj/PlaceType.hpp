#pragma once

#include <nn/types.h>

namespace fgobj
{
	enum class PlaceType : u8
	{
		NONE = 0x0,
		PICK_UP = 0x1,
		PICK_UP_FULL = 0x2,
		PICK_UP_SPECIAL = 0x3,
		PICK_UP_SPECIAL_FULL = 0x4,
		PICK_UP_SPECIAL_RELEASE = 0x5,
		PULL = 0x6,
		SHAKE_TREE = 0x8,
		SHAKE_TREE_BEES = 0x9,
		THROW = 0xa,
		BURY = 0xb,
		PLANT = 0xc,
		DISPLAY = 0xd,
		CUT_TREE = 0xe,
		CUT_TREE_BEES = 0xf,
		HIT_ITEM = 0x10,
		HIT_COIN_STONE = 0x11,
		BREAK_ROCK = 0x12,
		DIG_HOLE = 0x13,
		DIG_ITEM = 0x14,
		DIG_STUMP = 0x1b,
		FILL = 0x1c,

		FALL_ITEM = 0x21,
		THROW_SWAP_AFTER_PICK_UP = 0x22,
	};
}
