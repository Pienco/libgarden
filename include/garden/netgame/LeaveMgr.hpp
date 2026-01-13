#pragma once

#include "PlayerNo.hpp"

namespace netgame
{
	// only used for leaving village
	class LeaveMgr
	{
	
	public:

		auto& GetState() { return m_State; }

		void StartLeave(bool unknown);

	private:

		u8 m_State;
		u8 data[0x253f];
	};
	ASSERT_SIZE(LeaveMgr, 0x2540);
}
