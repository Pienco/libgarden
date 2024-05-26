#ifndef BS_LAYOUT_HPP
#define BS_LAYOUT_HPP

#include "ssys/ma/lyt/Layout.hpp"
#include "ssys/ma/lyt/LayoutMgr.hpp"
#include "ssys/ma/lyt/Animation.hpp"

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

	virtual void Draw() override;
	virtual void Update() override;

	inline void Register(bool bottomScreen = true)
	{
		ssys::ma::lyt::LayoutMgr::Get()->Register(this, bottomScreen);
	}

	inline void Initialize(const char* name, const ArcReader* reader = nullptr, u8 layer = 0, u32 unk = 0x5800)
	{
		Build(name, reader, unk);
		SetLayer(layer);
	}

	FORCE_INLINE inline bool AnimateFinish(Animation& anim)
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

#endif
