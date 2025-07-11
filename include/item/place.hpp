#ifndef ITEM_PLACE_HPP
#define ITEM_PLACE_HPP

#include "item/Item.hpp"

namespace item
{

	enum class TreeShakeType : u8
	{
		NONE,
		FRUIT,
		ITEM,
		BEES,
		FRUIT_DIE
	};

	TreeShakeType GetShake(Item& outItemAfterShake, const Item& shaken);

	enum class PlaceType : u8
	{
		NONE,
		PICK_UP,
		PICK_UP_FULL,
	};

	s32 PlaceItem(PlaceType type, Item& replace, Item& item1, Item& item2, u8 x, u8 y, u8 u0, u8 u1, TreeShakeType shakeType, u8 u3, u8 u4);

	struct PlaceItemPacket
	{

		void ProcessShakeItemTree();
		
		Item replace;
		Item item1;
		Item item2;
		u8 placeTypeAndPlayerNo;
		u8 processFlags;
		u8 flags;
		std::array<u8, 3> spawnedItemPos;
		u8 stage;
		u8 x;
		u8 y;
	};
	ASSERT_SIZE(PlaceItemPacket, 0x16);
}

#endif
