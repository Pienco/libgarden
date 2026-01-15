#pragma once

#include "SvPlayer.hpp"

struct SvPlayerData
{
	std::array<SvPlayer, 4> players;
};
ASSERT_SIZE(SvPlayerData, 0x29200);

struct SvMainData
{
	u8 header[0x20];
	SvPlayerData players;
	u8 villagers[0x22be0];
	u8 strc[0x44bc];
	u8 minigame[0x28f4];
	u8 data850[0x850];
	u8 field[0xa480];
	u8 home [0x48cf];
	u8 data13[0x13];
	u8 data40[0x40];
	u8 unknown[0xf6de];
};
ASSERT_SIZE(SvMainData, 0x71880);

struct SvGardenPlus
{
	u8 header[0x80];
	SvMainData mainData;
	u8 otherData[0x18200];
};
ASSERT_SIZE(SvGardenPlus, 0x89b00);
