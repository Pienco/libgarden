#pragma once

#include "netgame/NetGameMgr.hpp"
#include "netgame/PlayerState.hpp"

class AcPlayer;

namespace netgame
{

	/**
	 * @return whether we are in multiplayer mode
	 */
	bool IsMultiPlayer();

	/**
	 * @return whether there is more than one player in the session
	 */
	bool IsMultiplePlayer();

	bool ExistsPlayer(PlayerNo player);
	u8 GetMask(PlayerNo player);

	/**
	 * @return whether the current field is "controlled" by this player (responsible for e.g. sending fish/insect state)
	 */
	bool IsFieldControl();

	// inline PlayerNo GetMyPlayerNo() { return NetGameMgr::Get()->GetMyPlayerNo(); }
	PlayerNo GetMyPlayerNo();
	bool IsHost();
	u8 GetPlayerCount();

	enum class Type : u8
	{
		NONE = 0,
		FRIEND_MATCH = 1,
		RANDOM_MATCH = 2,
		DREAM = 3
	};

	Type GetNetgameType();

	void EnqueuePacket(u8 type, PlayerNo target, const void* data = nullptr, size_t size = 0);

	void* GetStatePacket(StatePacketID id);

	/**
	 * @return PlayerState given by `player`. Returns state of player 0 if `player` is invalid. Never returns `nullptr`.
	 */
	PlayerState* GetPlayerState(PlayerNo player = PlayerNo::INVALID);

	AcPlayer* GetPlayer(PlayerNo player, bool skipCheck = true);
	inline AcPlayer* GetMyPlayer(bool skipCheck = true) { return GetPlayer(PlayerNo::MY_NO, skipCheck); }
	bool GetPlayerPosition(s32& x, s32& y, PlayerNo no = PlayerNo::MY_NO, bool skipCheck = true);


	enum class TourState : u8
	{
		NONE,
		TOUR_SET,
	};

	inline bool IsTourSet()
	{
		extern TourState s_TourState;
		return s_TourState == TourState::TOUR_SET;
	}

	inline PlayerNo GetTourRequestPlayerNo()
	{
		extern PlayerNo s_TourRequestPlayerNo;
		return s_TourRequestPlayerNo;
	}
}
