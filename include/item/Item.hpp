#ifndef ITEM_ITEM_HPP
#define ITEM_ITEM_HPP

#include "types.h"
#include "item/resource.hpp"

namespace item
{

	union Item
	{
		constexpr Item(u32 data) : raw(data) { }
		constexpr Item() : id(ID::EMPTY), flags { } { }
		Item(ID id);

		bool IsEmpty() const;
		const ParamItemEntry* GetParamItemEntry() const;
		Kind GetKind() const;
		u16 GetIconID() const;
		const char* GetIconName() const;

		struct
		{
			ID id;
			u16 flags;
		};
		u32 raw;

	private:

		s32 ToNonFgID() const;

	};
	ASSERT_SIZE(Item, 4);
}

#endif
