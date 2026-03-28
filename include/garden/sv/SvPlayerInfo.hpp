#pragma once

#include <nn/types.h>

#include <array>

struct SvPlayerIdentity
{
	friend constexpr bool operator==(const SvPlayerIdentity&, const SvPlayerIdentity&) = default;

	u16 playerId;
	std::array<char16, 9> name;
	u8 gender;
	u8 unknown;
};
ASSERT_SIZE(SvPlayerIdentity, 0x16);

struct SvPlayerTown
{
	friend constexpr bool operator==(const SvPlayerTown&, const SvPlayerTown&) = default;

	u16 townId;
	std::array<char16, 9> name;
	u8 language;
	u8 unknown;
};
ASSERT_SIZE(SvPlayerTown, 0x16);

struct SvPlayerInfo
{
	friend constexpr bool operator==(const SvPlayerInfo&, const SvPlayerInfo&) = default;

	SvPlayerIdentity identity;
	SvPlayerTown town;
	u8 country;
	u8 region;
};
ASSERT_SIZE(SvPlayerInfo, 0x2e);
