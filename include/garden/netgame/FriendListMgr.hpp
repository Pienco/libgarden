#pragma once

#include "PlayerNo.hpp"
#include "AvatarId.hpp"

namespace netgame
{

	class FriendListMgr
	{
	public:
		
		s32 FindBestFriend(const u32& principal, const AvatarId& avatar);

		bool IsRegisteredBestFriend(const u32& principal, const AvatarId& avatar)
		{
			return FindBestFriend(principal, avatar) >= 0;
		}

	private:
		u8 data[0x42ac];
	};
	ASSERT_SIZE(FriendListMgr, 0x42ac);
}
