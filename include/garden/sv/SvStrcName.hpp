#pragma once

#include <nn/types.h>

struct SvStrcName
{
	enum Name : u8
	{
		POLICE_A = 0x4c,
		POLICE_B = 0x4d,
		CAFE = 0x4e,
		RESET = 0x4f,
		OFFICE_A = 0x50,
		OFFICE_B = 0x51,
		OFFICE_C = 0x52,
		OFFICE_D = 0x53,
		STATION_A = 0x54,
		STATION_B = 0x55,
		STATION_C = 0x56,
		STATION_D = 0x57,
		RECYCLE = 0x58,
		CROSSING = 0x5a,
		BBS = 0x5b,
		PIER = 0x5c,
		BOAT = 0x5d,
		TENT_FORTUNE = 0x5e,
		TENT_CAMP = 0x5f,
		TENT_TSUNEKICHI = 0x60,
		CEREMONY_A = 0x61,
		CEREMONY_B = 0x62,
		TABLE_HARVEST = 0x63,
		CARNIVAL_STAGE = 0x64,
		BBS_CD = 0x65,
		STAND_TSUNEKICHI = 0x66,
		DREAM_BED = 0x67,
		PIER_V = 0x68,
		TOURDESK = 0x69,
		HNW_RENT = 0x6a,
		SIGNBOARD_00 = 0x6b,
		SIGNBOARD_01 = 0x6c,
		SIGNBOARD_02 = 0x6d,
		SIGNBOARD_03 = 0x6e,
		SIGNBOARD_04 = 0x6f,
		SIGNBOARD_05 = 0x70,
		SIGNBOARD_06 = 0x71,
		SIGNBOARD_07 = 0x72,
		SIGNBOARD_08 = 0x73,
		SIGNBOARD_09 = 0x74,
		SIGNBOARD_10 = 0x75,
		SIGNBOARD_11 = 0x76,
		SIGNBOARD_12 = 0x77,
		SIGNBOARD_13 = 0x78,
		SIGNBOARD_14 = 0x79,
		SIGNBOARD_15 = 0x7a,
		SIGNBOARD_16 = 0x7b,
		SIGNBOARD_17 = 0x7c,
		SIGNBOARD_18 = 0x7d,
		SIGNBOARD_19 = 0x7e,
		RV_CAR_00 = 0x7f,
		RV_CAR_01 = 0x80,
		FORTUNE = 0x81,
		DREAM = 0x82,
		LIVEHOUSE = 0x83,
		MUSEUM = 0x84,
		SHOP = 0x85,
		GARDEN = 0x86,
		SHOESHOP = 0x87,
		CUT = 0x88,
		TAILOR = 0x89,
		ACCESHOP = 0x8a,
		ESTATE = 0x8b,
		POST = 0x8c,
		PHOTOBOX = 0x8d,
		DTN_LAMP = 0x8e,
		DTN_BENCH = 0x8f,
		BRIDGE_00_N_S = 0x90,
		CLOCK_FLOWER = 0xf9,
		BARRICADE_L = 0xfa,
		BARRICADE_R = 0xfb,
		COUNT,
		NONE = COUNT,
	};

	static bool IsTownHall(Name name);
	static bool IsTrainStation(Name name);
	static bool IsHobj(Name name);
	static bool IsDobj(Name name);
	static bool IsFobj(Name name);
	static bool IsFobjSp(Name name);

	Name name;
};
ASSERT_SIZE(SvStrcName, 0x1);
