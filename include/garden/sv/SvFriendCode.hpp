#pragma once

#include <nn/types.h>

struct SvFriendCode
{
	u32 principalId;
	u8 friendCode[8] {};
};
ASSERT_SIZE(SvFriendCode, 0xc);
