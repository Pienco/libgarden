#ifndef SEAD_CRITICALSECTION_HPP
#define SEAD_CRITICALSECTION_HPP

#include "types.h"

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

#endif
