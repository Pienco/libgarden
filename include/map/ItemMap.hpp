#ifndef MAP_ITEMMAP_HPP
#define MAP_ITEMMAP_HPP

#include "map/common.hpp"
#include "item/Item.hpp"

namespace map
{

	using ItemRow = std::array<item::Item, GetChunkSize().x()>;
	using ItemGrid = std::array<ItemRow, GetChunkSize().y()>;

	struct ItemChunk
	{
		ItemGrid items;
	};
	ASSERT_SIZE(ItemChunk, 0x400);

	struct Bg
	{
		u16 id;
		std::array<ItemChunk*, 2> chunks;
	};
	ASSERT_SIZE(Bg, 0xc);

	enum class ItemMapID : u8
	{
		NONE
	};

	class ItemMap
	{

	public:

		const item::Item& GetItem(Position pos, u8 layer = 0) const;
		bool PlaceItem(const item::Item& item, Position pos, u8 layer);
	
	private:

		Rect m_Rect;
		Rect m_Rect2;
		Bg* m_pBgs;
		void* m_pMapChunks;
		s32 unk1;
		s32 unk2;
		std::array<ItemChunk*, 2> m_pItemChunks;
	};
	ASSERT_SIZE(ItemMap, 0x38);
}

#endif
