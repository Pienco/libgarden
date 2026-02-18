#pragma once

#include <nn/types.h>

struct NpcAssistPacket
{
	enum Type : u8
	{
		TOUR_DESK = 0x1c,
	};

	Type type;
};
