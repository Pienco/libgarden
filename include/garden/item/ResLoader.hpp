#pragma once

#include "../g3d/ResourceLoader.hpp"

namespace item
{
	class ResLoader : public g3d::ResourceLoader
	{
	public:

	private:
		s32 unknown0;
		s32 unknown1;
		s32 unknown2;
	};
	ASSERT_SIZE(ResLoader, 0x114);
}
