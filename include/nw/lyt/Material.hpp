#ifndef NW_LYT_MATERIAL_HPP
#define NW_LYT_MATERIAL_HPP

#include "types.h"
#include "nw/lyt/TexMap.hpp"

namespace nw::lyt
{
	struct Color
	{
		u8 r, g, b, a;
	};

	class Material final
	{
	
	public:

		virtual ~Material();

		void SetTexture(size_t index, const TextureInfo& info)
		{
			((TexMap*)m_pElements)[index].Set(info);
			m_Flags &= 0xfb;
		}

	private:

		u8 data[0xc];
		Color m_Colors[7];
		u32 m_Capacity;
		u32 m_Count;
		void* m_pElements;
		char m_Name[21];
		u8 m_Flags;
		INSERT_PAD(2);
	};
	ASSERT_SIZE(Material, 0x50);
}

#endif
