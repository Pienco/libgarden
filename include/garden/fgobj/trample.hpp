#pragma once

#include "../netgame/netgame.hpp"
#include "../stage/stage.hpp"

namespace fgobj
{
	struct TramplePacket
	{
		TramplePacket();
		constexpr TramplePacket(SvFgName replace, stage::Name stage, u8 x, u8 z) : replace {replace}, stage {stage}, x {x}, z {z}
		{
		}

		void Process();
		void Send() { netgame::EnqueuePacket(0x47, netgame::TARGET_ALL, this, sizeof(*this)); }

		SvFgName replace;
		stage::Name stage = stage::Name::DUMMY;
		u8 x {};
		u8 z {};
		u8 padding {};
	};
	ASSERT_SIZE(TramplePacket, 8);
}
