#pragma once

#include "PlayerAction.hpp"
#include "../stage/Name.hpp"
#include "../netgame/PlayerNo.hpp"

#include <memory>

struct PACKED PlayerState
{
	stage::Name stage; // 0x0
	PlayerAction::Name actionName; // 0x1
	PlayerAction::CompactXZ position; // 0x2
	u16 rotation; // 0x6
	u8 counter; // 0x8
	struct PACKED Flags
	{
		bool isRetrieveTool : 1;
		bool isThink2 : 1;
		bool isMoving : 1;
		bool isPushedByCollision : 1;
		u8 flags_1 : 1;
		bool isSwimming : 1;
		bool isSittingBoat : 1;
		bool isSitSleep : 1;
		u8 flags1 : 8;
		bool isSitting : 1;
		bool isSittingStrc : 1;
		bool isSittingOther : 1;
		bool isDialog : 1;
		bool unk3 : 1;
		bool isSleeping : 1;
		bool unk4 : 1;
	} flags; // 0x9
	u8 chairDist; // 0xc
	u8 pad;
	PlayerAction action; // 0xe

	template<typename T> requires (sizeof(T) <= sizeof(action))
	T* GetAction()
	{
		return action.GetAction<T>();
	}

	template<typename T> requires (sizeof(T) <= sizeof(action) && std::is_trivially_destructible_v<T>)
	PlayerState* ConstructAction(auto&&... args)
	{
		action.ConstructAction<T>(std::forward<decltype(args)>(args)...);
		return this;
	}

};
ASSERT_SIZE(PlayerState, 0x26);
ASSERT_OFFSET(PlayerState, PlayerState::action, 0xe);
