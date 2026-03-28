#pragma once

#include "SvPlayerInventory.hpp"
#include "SvPlayerInfo.hpp"

struct SvPlayerCharacter
{
	static constexpr size_t nameSize = 9;

	u8 data0[0x55a6];
	SvPlayerInfo info;
	u8 data1[0x12d];

	enum Flags: u8
	{
		UNK = 1 << 0,
		TPC_TAB_UNLOCKED = 1 << 1,
	};

	enum UnlockFlags2: u8
	{
		FRIEND_LIST_UNLOCKED = 1 << 5,
	};

	bool IsTpcTabUnlocked() const { return (flags & Flags::TPC_TAB_UNLOCKED) != 0; }
	bool IsFriendListUnlocked() const { return (flags2 & UnlockFlags2::FRIEND_LIST_UNLOCKED) != 0; }

	Flags flags;
	u8 data2[0x1d];
	u8 flags2;
	u8 data3[0x146c];
};
ASSERT_OFFSET(SvPlayerCharacter, SvPlayerCharacter::info.identity.name, 0x55a8);
ASSERT_OFFSET(SvPlayerCharacter, SvPlayerCharacter::flags, 0x5701);
ASSERT_OFFSET(SvPlayerCharacter, SvPlayerCharacter::flags2, 0x571f);
ASSERT_SIZE(SvPlayerCharacter, 0x6b8c);

struct SvPlayer
{
	constexpr const SvPlayerInfo& GetInfo() const { return character.info; }

	SvPlayerCharacter character;
	u8 data[0x44];
	SvPlayerInventory inventory;
	u8 data2[0x1b78];
};
ASSERT_OFFSET(SvPlayer, SvPlayer::inventory, 0x6bd0);
ASSERT_SIZE(SvPlayer, 0xa480);
