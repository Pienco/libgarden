#pragma once

#include <nn/types.h>

namespace demo
{
	enum class OrderID : u8
	{
		ORDER_0 = 0,
		INTERACT = 1,
		DEFAULT_TALK = 2,
		ORDER_3 = 3,
		WARP = 4,
		ORDER_5 = 5,
		CREDITS = 6,
		PLAYER_THINK = 7,
		ISLAND_FORCE_LEAVE_THINK = 8,
		ORDER_9 = 9,
		SAVE = 10,
		ORDER_11 = 11,
		NETGAME_LOCK = 12,
		ORDER_13 = 13,
		REVOKED_PLAYER_CONTROL = 14,
		ORDER_15 = 15
	};

	bool CheckOrder(OrderID id, bool checkState = false);
	void MakeOrderIslandForceLeaveThink();
	void MakeOrderPlayerThink(u8 param);
	bool MakeOrderNetgameLock();
	void RevokeNetgameLockOrder();
}
