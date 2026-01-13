#pragma once

#include "Command.hpp"

namespace net::nex
{
	class Error
	{
	
	public:

		void Set(Command::ID cmd, u8 type = 6);

	private:

		u8 data[0xc];

	};
	ASSERT_SIZE(Error, 0xc);
}
