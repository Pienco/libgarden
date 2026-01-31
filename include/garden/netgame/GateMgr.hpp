#pragma once

#include "PlayerNo.hpp"

namespace netgame
{
	class GateMgr
	{
	public:
		bool IsOpen() const { return m_CloseFlags != 0; }
	private:
		u8 data[6];
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
