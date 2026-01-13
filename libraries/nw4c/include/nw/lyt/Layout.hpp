#pragma once

#include "nw/lyt/Pane.hpp"

namespace nw::lyt
{

	class Layout
	{
	public:
		Pane* GetRootPane() { return m_pRootPane; }

	private:
		u8 m_Data[0x10];
		Pane* m_pRootPane;
		u8 m_Data2[0xc];
	};
	ASSERT_SIZE(Layout, 0x20);
}
