#ifndef	AC_ACPLAYER_HPP
#define AC_ACPLAYER_HPP

#include "netgame/net.hpp"
#include "netgame/PlayerState.hpp"

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

	using PlayerState = netgame::PlayerState;
	using ActionPosition = netgame::ScaledPosition;

	u8 GetAction() const { return m_CurrentAction; }
	float& GetCollisionSize() { return *(float*)((u8*)this + 0x4f4); }
	const Vector2i& GetMapPosition() const { return m_MapPosition; }
	netgame::PlayerNo GetNo() const { return m_PlayerNo; }
	u8 GetLocation() const { return *((u8*)this + 0x140); }

	/**
	 * @return a pointer to a copy of the current player state in static storage
	 */
	PlayerState* GetScratchState() const;

	bool DoAction(u8 id, PlayerState* state = nullptr, bool unk = false);
	bool PickUpItem(s32 x, s32 y, u8 mapId, u32 unk, bool testOnly = false);

	static AcPlayer* Get(netgame::PlayerNo no = netgame::PlayerNo::MY_NO, bool skipCheck = true)
	{ 
		return netgame::GetPlayer(no, skipCheck);
	}

	static bool GetMapPosition(s32& x, s32& y, netgame::PlayerNo no = netgame::PlayerNo::MY_NO, bool skipCheck = true)
	{
		return netgame::GetPlayerPosition(x, y, no, skipCheck);
	}

private:
	u8 m_Data0[0x39];
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

#endif
