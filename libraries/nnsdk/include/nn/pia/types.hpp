#pragma once

#include <nn/types.h>

namespace nn::pia
{

	struct [[gnu::packed]] StationId
	{
		constexpr operator bool() const { return value != invalid; }

		static constexpr u64 invalid = -3;

		u64 value {invalid};
	};

	using PrincipalId = u32;

	using StationIndex = u8;

}
