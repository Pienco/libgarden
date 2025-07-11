#ifndef NETGAME_PLAYERNO_HPP
#define NETGAME_PLAYERNO_HPP

#include "types.h"
#include "util/enum.hpp"

namespace netgame
{
	enum PlayerNo : u8
	{
		HOST = 0,
		PLAYER_0 = 0,
		PLAYER_1 = 1,
		PLAYER_2 = 2,
		PLAYER_3 = 3,
		INVALID = 4,
		MY_NO = 4,
		TARGET_ALL = 4,
		MAX_PLAYER_COUNT = 4,
	};

	DEFINE_INCREMENT_DECREMENT(PlayerNo)
}

#endif
