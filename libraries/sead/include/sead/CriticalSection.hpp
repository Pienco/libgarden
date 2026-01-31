#pragma once

#include <nn/types.h>

namespace sead
{
	class CriticalSection
	{
	public:
		void Enter();
		void Exit();
		
	private:
		u8 data[0x1c];
	};
}
