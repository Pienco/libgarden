#pragma once

#include "stage/common.hpp"
#include "stage/ID.hpp"
#include "item/Item.hpp"

namespace stage
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
		BgID id;
		std::array<ItemChunk*, 2> chunks;
	};
	ASSERT_SIZE(Bg, 0xc);

	enum class FieldID : u8
	{
		CURRENT = 0,
		NONE = 0,
	};

	FieldID GetFieldID(ID stage);
	ID GetStageID(FieldID field);

	class Field
	{

	public:

		const auto& GetChunkBounds() const { return m_ChunkBounds; }
		const auto& GetTileBounds() const { return m_TileBounds; }

		/**
		 * @return `nullptr` if not available
	 	 */
		item::Item* GetItem(Position pos, u8 layer = 0);

		/**
		 * @return `nullptr` if not available
	 	 */
		const item::Item* GetItem(Position pos, u8 layer = 0) const;
		bool PlaceItem(const item::Item& item, Position pos, u8 layer = 0);
	
	private:
		Rect m_ChunkBounds;
		Rect m_TileBounds;
		Bg* m_pBgs;
		void* m_pMapChunks;
		s32 unk1;
		s32 unk2;
		std::array<ItemChunk*, 2> m_pItemChunks;
	};
	ASSERT_SIZE(Field, 0x38);
}
