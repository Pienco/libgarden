#ifndef ITEM_ITEM_HPP
#define ITEM_ITEM_HPP

#include "types.h"
#include "item/resource.hpp"
#include "script/Word.hpp"

namespace item
{
	using ItemName = script::WordFix<33>;

	struct Item
	{
		constexpr Item(u32 data) : id((ID)(data & UINT16_MAX)), flags((u16)(data >> 16)) { }
		constexpr Item() : id(ID::EMPTY), flags { } { }
		Item(ID id);

		bool IsEmpty() const;
		bool IsUsual() const;
		const ParamItemEntry* GetParamItemEntry() const;
		Kind GetKind() const;
		u16 GetIconID() const;
		const char* GetIconName() const;
		ItemName GetName(void* myDesign = nullptr) const;

		static void GetName(script::WordPtr* out, const Item& item, void* myDesign = nullptr);

		ID id;
		u16 flags;

	private:

		s32 GetIndex() const;

	};
	ASSERT_SIZE(Item, 4);
}

#endif
