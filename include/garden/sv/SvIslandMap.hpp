#pragma once

#include "SvBgName.hpp"
#include "SvFgBlock.hpp"
#include "SvStrc.hpp"

struct SvIslandMap
{
	u8 unknown[2];
	SvBgName bgs[4][4];
	SvFgBlock blocks[2][2];
	SvStrc strc[2];
};
ASSERT_SIZE(SvIslandMap, 0x102a);
