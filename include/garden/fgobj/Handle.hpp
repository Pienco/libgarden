#pragma once

#include <nn/types.h>

namespace fgobj
{
	struct Handle
	{
		constexpr Handle() = default;
		explicit constexpr Handle(s32 value) : value {value} {}
		constexpr operator bool() { return value >= 0; }
		s32 value = -1;
	};
}
