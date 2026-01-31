#pragma once

#include "Base.hpp"

class BsDemoCancelMgr : public Base
{

public:

	static void EnableCancel()
	{
		if (s_pInstance != nullptr)
			s_pInstance->m_State = 1;
	}

private:

	u8 m_State;
	s32 m_Timer;
	s32 m_MaxTime;

	static BsDemoCancelMgr* s_pInstance;
};
ASSERT_SIZE(BsDemoCancelMgr, 0x20);
