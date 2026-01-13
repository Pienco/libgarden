#pragma once

#include "../ssys/ma/lyt/Layout.hpp"
#include "../ssys/ma/lyt/LayoutMgr.hpp"
#include "../ssys/ma/lyt/Animation.hpp"

using ArcReader = ssys::ma::lyt::ArcResAccReader;
using Animation = ssys::ma::lyt::Animation;
using Pane = nw::lyt::Pane;
using Bounding = nw::lyt::Bounding;
using Group = nw::lyt::Group;
using TextBox = nw::lyt::TextBox;

class Layout final : public ssys::ma::lyt::Layout
{

public:

	Layout();
	virtual ~Layout() override;

	virtual void DrawSave() override;
	virtual void UpdateProj() override;

	void RegisterForDrawing(bool bottomScreen = true)
	{
		ssys::ma::lyt::LayoutMgr::Get()->Register(this, bottomScreen);
	}

	void Initialize(const char* name, const ArcReader* reader = nullptr, u8 layer = 0, u32 cmdCacheSize = 0x100)
	{
		Build(name, reader, cmdCacheSize);
		SetLayer(layer);
	}

	bool AnimateFinish(Animation& anim)
	{
		if (!anim.Finish())
		{
			Animate();
			return false;
		}
		return true;
	}

private:

};
ASSERT_SIZE(Layout, 0x14c);

