#ifndef ITEM_FISH_HPP
#define ITEM_FISH_HPP

#include "types.h"

namespace item
{
	enum class FishID : u8
	{
		TANAGO = 0x00,
		OIKAWA = 0x01,
		FUNA = 0x02,
		COUNT = 0x6b,
		INVALID = COUNT,
	};

}

#endif
