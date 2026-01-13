#pragma once

#include "common.hpp"
#include "Handle.hpp"
#include "../player/PlayerNumber.hpp"

namespace fgobj
{
	struct UnitLock
	{
		Position8 pos;
		stage::Name stage;
		u8 flags;
		PlaceType type;

		constexpr bool IsLock() const { return stage != stage::Name::DUMMY; }
	};
	ASSERT_SIZE(UnitLock, 0x5);

	extern std::array<UnitLock, 32> s_UnitLocks;

	Handle LockUnit(PlaceType type, u8 x, u8 y, stage::Name stage, bool netgameSend = true);
	Handle GetUnitLockHandle(u8 x, u8 y, stage::Name stage = stage::Name::CURRENT);
	void UnlockUnit(u8 x, u8 y, stage::Name stage, PlayerNumber target = PlayerNumber::ALL);

	inline const auto& GetUnitLocks()
	{
		return s_UnitLocks;
	}
}
