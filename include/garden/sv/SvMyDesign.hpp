#pragma once

#include <nn/types.h>

struct SvMyDesign
{
	u8 data[0x870];
};
ASSERT_SIZE(SvMyDesign, 0x870);
