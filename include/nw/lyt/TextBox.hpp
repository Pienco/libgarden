#ifndef NW_LYT_TEXTBOX_HPP
#define NW_LYT_TEXTBOX_HPP

#include "nw/lyt/Pane.hpp"

namespace nw::lyt
{

	class TextBox : Pane
	{

	public:

	private:

		u8 m_Data[0x34];
	};
	ASSERT_SIZE(TextBox, 0x108);
}

#endif
