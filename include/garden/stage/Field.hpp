#pragma once

#include "common.hpp"
#include "Name.hpp"
#include "../item/Item.hpp"

#include <array>

namespace stage
{
	using ItemRow = std::array<item::Item, GetBlockSize().x()>;
	using ItemGrid = std::array<ItemRow, GetBlockSize().y()>;

	struct ItemBlock
	{
		ItemGrid items;
	};
	ASSERT_SIZE(ItemBlock, 0x400);

	struct Bg
	{
		BgID id;
		std::array<ItemBlock*, 2> blocks;
	};
	ASSERT_SIZE(Bg, 0xc);

	enum class FieldName : u8
	{
		CURRENT = 0,
		NONE = 0,
	};

	FieldName GetFieldName(Name stage);
	Name GetStage(FieldName field);

	class Field
	{

	public:

		const auto& GetBlockBounds() const { return m_BlockBounds; }
		const auto& GetUnitBounds() const { return m_UnitBounds; }

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
		Rect m_BlockBounds;
		Rect m_UnitBounds;
		Bg* m_pBgs;
		void* m_pMapBlocks;
		void* m_pGrass;
		void* m_pGrass2;
		std::array<ItemBlock*, 2> m_pItemBlocks;
	};
	ASSERT_SIZE(Field, 0x38);
}
