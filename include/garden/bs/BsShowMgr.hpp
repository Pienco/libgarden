#pragma once

#include "Base.hpp"
#include "../item/Item.hpp"
#include "../netgame/PlayerNo.hpp"
#include "nn/math/Vector.hpp"

class BsShowMgr : public Base
{
public:

	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wconversion"

	struct PACKED ShowPacket
	{
		static constexpr u32 positionScale = 4;

		constexpr ShowPacket() = default;
		constexpr ShowPacket(const SvFgName& item, const Vector3& pos) :
			cmd {1},
			id {item::ToInsectFishID(item)},
			x {static_cast<u32>(pos.x) / positionScale},
			z {static_cast<u32>(pos.z) / positionScale} { }

		u8 cmd : 2 {};
		u32 id : 7 {};
		u32 x : 10 {};
		u32 z : 10 {};
	};
	ASSERT_SIZE(ShowPacket, 4);

	#pragma GCC diagnostic pop

	static BsShowMgr* Get() { return s_pInstance; }

	static void Show(const SvFgName& item, const Vector3& position);
	static void InitializeFromPacket(netgame::PlayerNo sender, const ShowPacket& packet);

private:

	static BsShowMgr* s_pInstance;
};
