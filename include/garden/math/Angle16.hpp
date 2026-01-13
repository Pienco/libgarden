#pragma once

#include <nn/types.h>

namespace math
{
	struct Angle16
	{

		static Angle16 Atan2(float x, float y);

		u16 value;
	};
}
