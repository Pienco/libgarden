#ifndef NW_LYT_GROUP_HPP
#define NW_LYT_GROUP_HPP

#include "types.h"

namespace nw::lyt
{

	class Group
	{

	public:

	private:

		u8 m_Data[0x2c];
	};
	ASSERT_SIZE(Group, 0x2c);
}

#endif
