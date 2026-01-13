#pragma once

#include <nn/types.h>

namespace netgame
{
	class JoinMgr
	{
	
	public:

		u8& GetState() { return m_State; }

		void StartEntry();

	private:
		u8 m_State;
		u8 data[0x17];
	};
	ASSERT_SIZE(JoinMgr, 0x18);
}
