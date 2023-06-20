#ifndef BS_LAYOUT_HPP
#define BS_LAYOUT_HPP

#include "ssys/ma/lyt/Layout.hpp"
#include "ssys/ma/lyt/LayoutMgr.hpp"
#include "ssys/ma/lyt/Animation.hpp"

using ArcReader = ssys::ma::lyt::ArcResAccReader;
using Animation = ssys::ma::lyt::Animation;
using Pane = nw::lyt::Pane;
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

private:

};
ASSERT_SIZE(Layout, 0x14c);

#endif
