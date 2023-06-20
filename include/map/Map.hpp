#ifndef MAP_MAP_HPP
#define MAP_MAP_HPP

#include "types.h"


namespace map
{

	enum class MapID : u8
	{
		DUMMY = 0xa5,
	};

	MapID GetCurrentMapID();
}

#endif
