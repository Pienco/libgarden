#pragma once

#include "SvFgName.hpp"

struct SvFdFgBlock
{
	SvFgName items[16][16];
};
ASSERT_SIZE(SvFdFgBlock, 0x400);
