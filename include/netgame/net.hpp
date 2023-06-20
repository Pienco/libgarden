#ifndef NETGAME_NET_HPP
#define NETGAME_NET_HPP

#include "types.h"
#include "base/AcPlayer.hpp"

namespace netgame
{

	void EnqueuePacket(u8 type, u8 target, const void* data, size_t size);

	AcPlayer* GetPlayerActor(u8 no, bool skipCheck);
	inline AcPlayer* GetMyPlayerActor(bool skipCheck = true) { return GetPlayerActor(4, skipCheck); }
	bool GetPlayerCoordinates(u32* outX, u32* outY, u8 no = 4, bool skipCheck = true);
}

#endif
