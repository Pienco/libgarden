#ifndef NETGAME_NET_HPP
#define NETGAME_NET_HPP

#include "types.h"
#include "ac/AcPlayer.hpp"
#include "netgame/NetGameMgr.hpp"

namespace netgame
{

	bool IsMultiPlayer();
	bool IsMultiplePlayer();

	void EnqueuePacket(u8 type, PlayerNo target, const void* data, size_t size);

	AcPlayer* GetPlayerActor(u8 no, bool skipCheck);
	inline AcPlayer* GetMyPlayerActor(bool skipCheck = true) { return GetPlayerActor(4, skipCheck); }
	bool GetPlayerCoordinates(u32* outX, u32* outY, u8 no = 4, bool skipCheck = true);

	inline PlayerNo GetMyPlayerNo() { return NetGameMgr::Get()->GetMyPlayerNo(); }


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

#endif
