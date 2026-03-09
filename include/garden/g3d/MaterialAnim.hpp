#pragma once

#include <nn/types.h>

namespace g3d
{
	class MaterialAnim
	{
	public:

	private:
		u8 data[0x20];
	};
	ASSERT_SIZE(MaterialAnim, 0x20);
}
