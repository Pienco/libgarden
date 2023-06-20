#ifndef ITEM_ID_HPP
#define ITEM_ID_HPP

#include "types.h"

namespace item
{

	enum class ID : u16
	{
		FG_ITEM_BEGIN = 0,
		FG_ITEM_END = 0xfe,

		ITEM_BEGIN = 0x2000,

		ITEM_END = 0x372b,

		EMPTY = INT16_MAX - 1,
	};
}

#endif
