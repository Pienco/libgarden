#pragma once

#include <nn/types.h>

namespace applet
{
	class ErrEulaMgr
	{
	public:

	private:
		u8 data[0xfb4];
	};
	ASSERT_SIZE(ErrEulaMgr, 0xfb4);
}
