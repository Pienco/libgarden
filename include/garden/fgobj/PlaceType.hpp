#pragma once

#include <nn/types.h>

namespace fgobj
{
	enum class PlaceType : u8
	{
		NONE,
		PICK_UP,
		PICK_UP_FULL,

		TREE_CUT = 0xe,
		TREE_CUT_BEES = 0xf,

		BREAK_ROCK = 0x12,

		FLOAT = 0x21,
	};
}
