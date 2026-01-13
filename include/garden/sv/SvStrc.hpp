#pragma once

#include "SvStrcName.hpp"
#include <nn/math/Vector.hpp>

struct SvStrc
{
	SvStrcName name;
	u8 pad;
	math::Vector2u8 position;
};
ASSERT_SIZE(SvStrc, 0x4);
