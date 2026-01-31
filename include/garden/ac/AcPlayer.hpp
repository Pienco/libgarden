#pragma once

#include "../netgame/netgame.hpp"
#include "../player/PlayerState.hpp"

#include "DemoActor.hpp"

class PlayerSimpleMessage
{
public:

private:

	u8 data[0x108];
};
ASSERT_SIZE(PlayerSimpleMessage, 0x108);


class AcPlayer : public UtlBaseDemoActor, public PlayerSimpleMessage
{
public:

	using ActionName = PlayerAction::Name;

	struct PACKED ActionFlags
	{
		// 0x0
		bool needProcess : 1;
		u8 b0 : 4;
		bool isControlled : 1;
		u8 b0_2 : 2;

		// 0x1
		u8 b1 : 1;
		bool needRetrieveTool : 1;
		u8 unk : 1;
		bool walkDone : 1;
		u8 b1_2 : 2;
		bool emoteDone : 1;
		u8 b1_3 : 1;

		// 0x2
		u8 b2 : 8;
		// 0x3
		u8 b3 : 8;
		// 0x4
		u8 b4 : 8;

		// 0x5
		u8 b5 : 6;
		bool msg1 : 1;
		bool msg2 : 1;

		// 0x6
		u8 b6 : 4;
		bool isGrassSound : 1;
		u8 b6_2 : 3;

		// 0x7
		u8 b7 : 7;
		bool cameraChanged : 1;

		// 0x8
		u8 b8 : 8;

		// 0x9
		u8 b9 : 5;
		bool enableIndoorSe : 1;
		u8 b9_2 : 2;

		// 0xa
		u8 ba : 8;

		// 0xb
		u8 bb : 7;
		bool enableWarp : 1;
	};
	ASSERT_SIZE(ActionFlags, 0xc);

	bool IsControlled() const { return m_ActionFlags.isControlled; }

	u8 GetAction() const { return m_CurrentAction; }
	float& GetCollisionSize() { return *(float*)((u8*)this + 0x4f4); }
	const Vector2i& GetMapPosition() const { return m_MapPosition; }
	netgame::PlayerNo GetNo() const { return m_PlayerNo; }
	u8 GetLocation() const { return *((u8*)this + 0x140); }
	Vector3 GetFacingPosition(float distance, bool withHeight = false) const
	{
		Vector3 result;
		GetPositionTo(result, GetRotation().y, distance, withHeight);
		return result;
	}

	/**
	 * @return a pointer to a copy of the current player state in static storage
	 */
	PlayerState* GetScratchState() const;

	bool DoAction(ActionName name, const PlayerState* state = nullptr, bool unk = false);
	bool PickUpItem(s32 x, s32 y, u8 mapId, u32 unk, bool testOnly = false);

private:
	ActionFlags m_ActionFlags;
	u8 m_Data0[0x2d];
	u8 m_CurrentAction;
	u8 m_PreviousAction;
	u8 m_NextAction;
	netgame::PlayerNo m_PlayerNo;
	u32 unk;
	u8 m_Model[0x270];
	Vector3 m_MapPositionF;
	u8 m_Data1[0x4c];
	Vector2i m_MapPosition;
	Vector2i m_MapPosition2;
	u8 m_Data[0x10d8];
};
ASSERT_SIZE(AcPlayer, 0x1564);
