#pragma once

#include <nn/types.h>

#include <array>

struct SvBestFriend
{
	u8 data[0x14b0];
};
ASSERT_SIZE(SvBestFriend, 0x14b0);

struct SvBestFriendList
{
	bool HasFriend() const;
	SvBestFriend* GetEntry(size_t index);

	u64 header;
	std::array<SvBestFriend, 32> entries;
};
ASSERT_SIZE(SvBestFriendList, 0x29608);
