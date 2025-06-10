#ifndef SV_SVPLAYERINVENTORY_HPP
#define SV_SVPLAYERINVENTORY_HPP

#include "item/Item.hpp"

struct SvPlayerInventory
{
	enum ItemAppearance : u8
	{
		DEFAULT,
		PRESENT,
		MAIL,
		WRAP_PRESENT
	};

	static constexpr size_t SIZE = 0x10;

	const item::Item* GetItem(size_t index, ItemAppearance* out = nullptr) const;
	bool HasItem(const item::Item& item) const;
	bool AddItem(const item::Item& item, ItemAppearance appearance = DEFAULT, item::Item* out = nullptr);
	bool SetItem(size_t index, const item::Item& item, ItemAppearance appearance = DEFAULT, item::Item* out = nullptr);

	size_t GetCount(item::ItemOrID auto&& item) const
	{
		size_t result = 0;
		for (size_t i = 0; i < SIZE; i++)
		{
			if (*GetItem(i) == item)
				result++;
		}
		return result;
	}

	s32 Find(item::ItemOrID auto&& item) const
	{
		for (size_t i = 0; i < SIZE; i++)
		{
			if (*GetItem(i) == item) return i;
		}
		return -1;
	}
};

#endif
