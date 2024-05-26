#ifndef NW_LYT_TEXMAP_HPP
#define NW_LYT_TEXMAP_HPP

#include "types.h"
#include "nw/lyt/ArcResourceAccessor.hpp"

namespace nw::lyt
{

	class TexMap
	{
	
	public:

		inline void Set(const TextureInfo& info)
		{
			data = info.data;
			flags = ((info.format & 0xf) << 8) | (flags & 0xfffff0ff);
			Update();
		}

	private:

		void Update();

		std::array<u8, 0x10> data;
		u32 flags;
		u32 flags2;
		u32 flags3;
		u32 flags4;
	};
	ASSERT_SIZE(TexMap, 0x20);
}

#endif
