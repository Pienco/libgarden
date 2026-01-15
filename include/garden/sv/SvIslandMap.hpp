#pragma once

#include "SvBgName.hpp"
#include "SvFdFgBlock.hpp"
#include "SvStrc.hpp"

struct SvIslandMap
{
	u8 unknown[2];
	SvBgName bgs[4][4];
	SvFdFgBlock blocks[2][2];
	SvStrc strc[2];
};
ASSERT_SIZE(SvIslandMap, 0x102a);
