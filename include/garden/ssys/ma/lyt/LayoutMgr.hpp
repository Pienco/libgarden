#pragma once

#include "Layout.hpp"
#include "../../st/List.hpp"

#include <nw/lyt/GraphicsResource.hpp>
#include <nw/lyt/Drawer.hpp>

namespace ssys::ma::lyt
{
	class LayoutList : public st::List
	{

	};
	ASSERT_SIZE(LayoutList, 0xc);

	class LayoutMgr
	{
	public:
		static constexpr u32 topScreenWidth = 400;
		static constexpr u32 bottomScreenWidth = 320;
		static constexpr u32 topScreenHeight = 240;
		static constexpr u32 bottomScreenHeight = 240;

		static LayoutMgr* Get() { return s_pInstance; }

		auto& GetResource() { return m_Resource; }
		auto& GetDrawer() { return m_Drawer; }

		void DrawBegin(u32 width, u32 height);

		void DrawBegin(bool isBottomScreen)
		{
			DrawBegin(isBottomScreen ? bottomScreenWidth : topScreenWidth, topScreenHeight);
		}

		void Register(Base2D* b2d, bool bottomScreen);

	private:
		virtual ~LayoutMgr();

		static LayoutMgr* s_pInstance;

		LayoutList m_DrawListA;
		LayoutList m_DrawListB;
		nw::lyt::GraphicsResource m_Resource;
		u8 data[0x64];
		nw::lyt::Drawer m_Drawer;
	};
	ASSERT_SIZE(LayoutMgr, 0xa08);
}
