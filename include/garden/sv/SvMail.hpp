#pragma once

#include <nn/types.h>

struct SvMail
{
	u8 data[0x280];
};
ASSERT_SIZE(SvMail, 0x280);
