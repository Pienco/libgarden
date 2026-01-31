#pragma once

#include <nn/types.h>

namespace nn::pia
{

	using u64 = uint64_t;
	using u32 = uint32_t;
	using u16 = uint16_t;
	using u8 = uint8_t;

	using s64 = int64_t;
	using s32 = int32_t;
	using s16 = int16_t;
	using s8 = int8_t;

	struct [[gnu::packed]] StationId
	{
		constexpr operator bool() const { return value != invalid; }

		static constexpr u64 invalid = -3;

		u64 value {invalid};
	};

	using PrincipalId = u32;

	using StationIndex = u8;

}
