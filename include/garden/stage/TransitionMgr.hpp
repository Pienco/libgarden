#pragma once

#include "Name.hpp"

namespace stage
{
	class TransitionMgr
	{
	public:
		bool Transition(Name stage, u8 typeA, u8 faderA, u8 typeB, u8 faderB);

		void SetReturnParam();

	private:
		u8 data[0x30];
	};

	TransitionMgr* GetTransitionMgr();

	bool Transition(Name stage, u8 typeA, u8 faderA, u8 typeB, u8 faderB);

	Name GetNext();
}
