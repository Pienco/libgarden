#pragma once

#include "PlayerNo.hpp"

namespace netgame
{
	class GateMgr
	{
	public:

		enum Flag
		{
			TRAIN_STATION,
			BOAT_TRIP,
			RANDOM_MATCH_TOUR,
			RANDOM_MATCH_PLAYER_JOINING,
			RANDOM_MATCH_PLAYER_LEAVING,
			UNKNOWN,
		};

		bool Open(Flag);
		bool IsOpen() const { return m_CloseFlags == 0; }
		bool IsClosed(Flag) const;
		bool Close(Flag);

	private:
		u8 m_CmdQueue[5];
		u8 m_CurrentCmd;
		u8 m_CloseFlags;
		u8 padding;
	};
	ASSERT_SIZE(GateMgr, 8);

	inline bool IsGateBestFriendsOnly()
	{
		extern u16 s_GateParam;
		return s_GateParam & 1;
	}
}
