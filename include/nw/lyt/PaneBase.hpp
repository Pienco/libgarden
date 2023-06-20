#ifndef NW_LYT_PANEBASE_HPP
#define NW_LYT_PANEBASE_HPP

#include "types.h"


namespace nw::lyt
{

	class PaneBase
	{
	
	public:

		virtual ~PaneBase();

	private:

		u8 m_Data[8];
	};
	ASSERT_SIZE(PaneBase, 0xc);
}

#endif
