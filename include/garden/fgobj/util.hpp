#pragma once

#include "common.hpp"

namespace fgobj
{

	enum FindUnitForPlayerCheck : u8
	{
		PUT,
		PLANT,
		DISPLAy,
	};

	bool FindPlaceableUnitAroundPlayer(s32& x, s32& z, u8& layer, FindUnitForPlayerCheck type = {}, bool placeInFront = false);
}
