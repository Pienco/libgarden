#pragma once

#include "Base.hpp"
#include "../item/Item.hpp"
#include "../netgame/PlayerNo.hpp"
#include "../netgame/packet.hpp"
#include "nn/math/Vector.hpp"

class BsShowMgr : public Base
{
public:

	static BsShowMgr* Get() { return s_pInstance; }

	static void Show(const item::Item& item, const math::Vector3& position);
	static void InitializeFromPacket(netgame::PlayerNo sender, const netgame::ShowPacket& packet);

private:

	static BsShowMgr* s_pInstance;
};
