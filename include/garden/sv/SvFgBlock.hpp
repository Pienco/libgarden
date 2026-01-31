#pragma once

#include "SvFgName.hpp"
#include "../field/types.hpp"

struct SvFgBlock
{
	SvFgName items[unitBaseNum][unitBaseNum];
};
ASSERT_SIZE(SvFgBlock, 0x400);
