#ifndef ITEM_MODELID_HPP
#define ITEM_MODELID_HPP

#include "types.h"

namespace item
{
	enum class ModelID : u8
	{
		DEFAULT,
		APPLE,
		ORANGE,
		COUNT = 0xaa,
	};
}

#endif
