#pragma once

#include <nn/types.h>

struct PlayerNumber
{
	enum Number : u8
	{
		HOST = 0,
		PLAYER_0 = 0,
		PLAYER_1 = 1,
		PLAYER_2 = 2,
		PLAYER_3 = 3,
		DUMMY = 4,
		ALL = 4,
		SELF = 4,
		COUNT = 4,
	};
	constexpr PlayerNumber() = default;
	constexpr PlayerNumber(Number value) : value {value} {}
	constexpr operator Number() const { return value; }
	Number value = DUMMY;
};
