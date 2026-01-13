#pragma once

#include "PlaceType.hpp"
#include "../g3d/ResourceLoader.hpp"
#include "../sv/SvFgName.hpp"
#include "../stage/Name.hpp"

namespace fgobj
{
	g3d::ResourceLoader* GetFgLut();

	struct Position8 { u8 x; u8 y; };
}
