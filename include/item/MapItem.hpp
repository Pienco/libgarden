#ifndef ITEM_MAPITEM_HPP
#define ITEM_MAPITEM_HPP

#include "item/Item.hpp"

namespace item
{

	struct MapItem
	{
		
		void Place();


		Item item;
		u8 map;
		u8 x;
		u8 y;
	};
	ASSERT_SIZE(MapItem, 8);
}

#endif
