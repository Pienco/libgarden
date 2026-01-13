#pragma once

#include <nn/types.h>

struct SvStrcName
{
	enum Name : u8
	{
		POLICE_A = 0x4c,
		POLICE_B = 0x4d,
		PIER_V = 0x68,
		TOURDESK = 0x69,
		HNW_RENT = 0x6a,
		NONE = 0xfc
	};

	static bool IsTownHall(Name name);
	static bool IsTrainStation(Name name);

	Name name;
};
ASSERT_SIZE(SvStrcName, 0x1);
