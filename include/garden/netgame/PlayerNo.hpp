#pragma once

#include <nn/types.h>

#include <utility>

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

	constexpr PlayerNo& operator++(PlayerNo& v)
	{
		v = static_cast<PlayerNo>(std::to_underlying(v) + std::underlying_type_t<PlayerNo> { 1 });
		return v;
	}
	constexpr PlayerNo operator++(PlayerNo& v, int)
	{
		const PlayerNo result = v;
		++v;
		return result;
	}
	constexpr PlayerNo& operator--(PlayerNo& v)
	{
		v = static_cast<PlayerNo>(std::to_underlying(v) - std::underlying_type_t<PlayerNo> { 1 });
		return v;
	}
	constexpr PlayerNo operator--(PlayerNo& v, int)
	{
		const PlayerNo result = v;
		--v;
		return result;
	}

	u8 GetMask(PlayerNo player);
}
