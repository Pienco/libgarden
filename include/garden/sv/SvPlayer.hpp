#ifndef SV_SVPLAYER_HPP
#define SV_SVPLAYER_HPP

#include "SvPlayerInventory.hpp"

struct PACKED SvPlayerCharacter
{
	static constexpr size_t nameSize = 9;

	// u32 checksum;
	// u8 hairstyle;
	// u8 haircolor;
	// u8 face;
	// u8 eyecolor;
	// u8 tan;
	// u8 unk;
	// item::Item outfit[7];
	// item::Item heldItem;
	u8 data0[0x55a8];
	std::array<char16_t, nameSize> name;
	u8 data1[0x147];

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
ASSERT_OFFSET(SvPlayerCharacter, SvPlayerCharacter::flags, 0x5701);
ASSERT_OFFSET(SvPlayerCharacter, SvPlayerCharacter::flags2, 0x571f);
ASSERT_SIZE(SvPlayerCharacter, 0x6b8c);

struct SvPlayer
{
	static SvPlayer* Get();

	SvPlayerCharacter character;
	u8 data[0x44];
	SvPlayerInventory inventory;
	u8 data2[0x1b78];
};
ASSERT_OFFSET(SvPlayer, SvPlayer::inventory, 0x6bd0);
ASSERT_SIZE(SvPlayer, 0xa480);

#endif
