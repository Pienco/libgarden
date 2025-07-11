#ifndef NETGAME_CONFIRMMACHINE_HPP
#define NETGAME_CONFIRMMACHINE_HPP

#include "netgame/MachineBitTable.hpp"

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
#endif