#pragma once

#include "../item/Kind.hpp"

struct PACKED SvFgName
{
	#include "SvFgName_Name.hpp"

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
			struct PACKED In
			{
				u16 : 14;
				u8 orientation : 2;
			} in;

			struct PACKED Out
			{
				u16 : 15;
				bool buried : 1;
			} out;
		} common;

		friend constexpr bool operator==(const Flags& left, const Flags& right)
		{
			return left.raw == right.raw;
		}
	};
	ASSERT_SIZE(Flags, 2);

	using Kind = item::Kind;

	explicit constexpr SvFgName(u32 data) : name((Name)(data & UINT16_MAX)), flags {(u16)(data >> 16)} { }
	constexpr SvFgName(Name name, Flags flags) : name(name), flags {flags} { }
	constexpr SvFgName() : name(Name::EMPTY), flags {} { }
	explicit SvFgName(Name name);

	friend constexpr bool operator==(const SvFgName& left, Name right) { return left.name == right; }
	friend constexpr bool operator==(const SvFgName& left, const SvFgName& right)
	{
		return left.name == right.name && left.flags == right.flags;
	}

	constexpr SvFgName& operator=(Name right)
	{
		name = right;
		return *this;
	}

	bool IsEmpty() const;
	bool IsUsual() const;
	Kind GetKind() const;
	u8 GetFgKind() const;

	explicit constexpr operator u32() const
	{
		return static_cast<u16>(name) + (flags.raw << 16);
	}

	static const SvFgName& GetEmpty() { return s_Empty; }

	static SvFgName s_Empty;

	Name name;
	Flags flags;
};
ASSERT_SIZE(SvFgName, 0x4);
