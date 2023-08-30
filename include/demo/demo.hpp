#ifndef DEMO_DEMO_HPP
#define DEMO_DEMO_HPP

#include "types.h"

namespace demo
{

	enum class OrderID : u8
	{
		ORDER_0 = 0,
		INTERACT = 1,
		DEFAULT = 2,
		ORDER_3 = 3,
		DO_NOTHING = 4,
		ORDER_5 = 5,
		ORDER_6 = 6,
		PLAYER_THINK = 7,
		ISLAND_FORCE_LEAVE_THINK = 8,
		ORDER_9 = 9,
		ORDER_10 = 10,
		ORDER_11 = 11,
		NOTHING_2 = 12,
		ORDER_13 = 13,
		REVOKED_PLAYER_CONTROL = 14,
		ORDER_15 = 15
	};

	bool CheckOrder(OrderID id, bool checkState = false);
	void MakeOrderIslandForceLeaveThink();
	void MakeOrderPlayerThink(u8 param);
}

#endif
