#pragma once

#include "../netgame/netgame.hpp"
#include "../sv/SvFgName.hpp"

class TourResult
{
public:

	static TourResult* Get() { return s_pInstance; }

	struct ChangeScorePacket
	{
		SvFgName item;
		s32 score;
		netgame::PlayerNo player;

		void Send(netgame::PlayerNo target) const
		{
			netgame::EnqueuePacket(0x43, target, this, sizeof(*this));
		}

	};
	ASSERT_SIZE(ChangeScorePacket, 0xc);

	void ChangeScore(netgame::PlayerNo player, s32 score, const SvFgName& item);

private:
	static TourResult* s_pInstance;
};
