#pragma once

#include "../sv/SvFgName.hpp"

struct PlayerHeadBankKeyword
{
	u8 hairStyle = 0x22;
	u32 hairColor = 0xffffffff;
	u32 eyeColor = 0xffffffff;
	SvFgName item {};
	u8 unknown0 = 0;
	u8 unknown1 = 200;
	u8 unknown2 = 200;
	u8 unknown3 = 0;
};
ASSERT_SIZE(PlayerHeadBankKeyword, 0x14);
