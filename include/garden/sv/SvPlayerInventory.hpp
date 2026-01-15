#pragma once

#include "SvFgName.hpp"

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

	using ItemArray = std::array<SvFgName, SIZE>;

	const SvFgName* GetItem(size_t index, ItemAppearance* out = nullptr) const;
	bool HasItem(const SvFgName& item) const;
	bool AddItem(const SvFgName& item, ItemAppearance appearance = DEFAULT, SvFgName* newItem = nullptr);
	bool SetItem(size_t index, const SvFgName& item, ItemAppearance appearance = DEFAULT, SvFgName* newItem = nullptr);
	s32 FindFirstEmptySlot();
	size_t GetFreeSlotCount();

	size_t GetCount(auto&& item) const
	{
		size_t result = 0;
		for (size_t i = 0; i < SIZE; i++)
		{
			if (*GetItem(i) == item)
				result++;
		}
		return result;
	}

	s32 Find(auto&& item) const
	{
		for (size_t i = 0; i < SIZE; i++)
		{
			if (*GetItem(i) == item) return i;
		}
		return -1;
	}

	ItemArray& GetItems() { return items; }

	ItemArray items;
	u8 data[0x1cf8];
};
ASSERT_SIZE(SvPlayerInventory, 0x1d38);
