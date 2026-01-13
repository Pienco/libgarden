#pragma once

#include "MachineBitTable.hpp"

namespace netgame
{

	class ConfirmMachine : public MachineBitTable
	{

	public:

		virtual ~ConfirmMachine();

	private:

	};
	ASSERT_SIZE(ConfirmMachine, 0x8);

}
