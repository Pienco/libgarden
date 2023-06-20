#ifndef ITEM_RESOURCE_HPP
#define ITEM_RESOURCE_HPP

#include "types.h"
#include "item/Kind.hpp"
#include "item/ID.hpp"

namespace item
{

	struct ParamItemEntry
	{
		u16	iconID;
		u16	price;
		u8 roomOrientation[6];
		Kind kind;
		u8 modelID;
		u8 unk[2];
		s8 priceMultiplier;
		u8 unk2[2];
		u8 ftr;
		u8 unk3[7];
		u8 type;
		u8 inventoryActionFlags;
		u8 unk4[3];
	};
	ASSERT_SIZE(ParamItemEntry, 0x1e);

	struct KindDataEntry
	{
		ID beginID;
		ID endID;
		size_t count;
		const char* name;
	};
	ASSERT_SIZE(KindDataEntry, 0xc);

	const KindDataEntry* GetKindDataEntry(Kind kind);
}

#endif
