#ifndef ITEM_ITEM_HPP
#define ITEM_ITEM_HPP

#include "types.h"
#include "item/resource.hpp"
#include "script/Word.hpp"

namespace item
{
	using ItemName = script::WordFix<33>;

	union Flags
	{
		u16 raw;

		union Unique
		{
			struct FruitTree
			{
				u8 fruitGrowth : 3;
				bool isPerfect : 1;
				u8 perfectDecay : 3;
				u8 isRandomPerfectFruit : 3;
			} fruitTree;

			u16 unique : 14;
		} unique;

		union Common
		{
			struct In
			{
				u16 : 14;
				u8 orientation : 2;
			} in;

			struct Out
			{
				u16 : 15;
				bool buried : 1;
			} out;
		} common;

		friend constexpr bool operator==(std::common_with<Flags> auto&& left, std::common_with<Flags> auto&& right)
		{
			return left.raw == right.raw;
		}
	};
	ASSERT_SIZE(Flags, 2);

	struct Item
	{
		constexpr Item(u32 data) : id((ID)(data & UINT16_MAX)), flags { (u16)(data >> 16) } { }
		constexpr Item() : id(ID::EMPTY), flags { } { }
		Item(ID id);

		friend constexpr bool operator==(std::common_with<Item> auto&& left, ID right) { return left.id == right; }
		friend constexpr bool operator==(std::common_with<Item> auto&& left, std::common_with<Item> auto&& right)
		{
			return left.id == right.id && left.flags == right.flags;
		}

		constexpr Item& operator=(ID right)
		{
			id = right;
			return *this;
		}

		bool IsEmpty() const;
		bool IsUsual() const;
		const ParamItemEntry* GetParamItemEntry() const;
		Kind GetKind() const;
		u16 GetIconID() const;
		const char* GetIconName() const;
		ItemName GetName(void* myDesign = nullptr) const;

		static void GetName(script::WordPtr* out, const Item& item, void* myDesign = nullptr);

		ID id;
		Flags flags;

	private:

		s32 GetIndex() const;

	};
	ASSERT_SIZE(Item, 4);
}

#endif
