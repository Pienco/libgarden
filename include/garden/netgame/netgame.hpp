#pragma once

#include "NetGameMgr.hpp"
#include "../sv/SvIslandMap.hpp"

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

	/**
	 * @return whether the current stage is "controlled" by this player (responsible for e.g. sending fish/insect state)
	 */
	bool IsStageControl();

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
	void SetNetGameType(Type);

	bool RequestOpenGateRandomMatch(GateMgr::Flag flag);
	bool RequestCloseGateRandomMatch(GateMgr::Flag flag);

	bool InitNet();
	inline void FiniNet() { NetGameMgr::Get()->FiniNet(); }
	bool StopNet();

	bool StartConnectBestFriend();
	bool IsConnectedBestFriend();

	void EnqueuePacket(u8 type, PlayerNo target, const void* data = nullptr, size_t size = 0);

	void* GetStatePacket(StatePacketID id);

	SvIslandMap* GetIslandMap();

	inline NetGameMgr* GetMgr() { return NetGameMgr::Get(); }
}
