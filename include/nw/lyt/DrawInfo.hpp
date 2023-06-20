#ifndef NW_LYT_DRAWINFO_HPP
#define NW_LYT_DRAWINFO_HPP

#include "types.h"

namespace nw::lyt
{

	class DrawInfo
	{

	public:

	private:

		u8 m_Data[0x8c];
	};
	ASSERT_SIZE(DrawInfo, 0x8c);
}

#endif
