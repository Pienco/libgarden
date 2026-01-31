#pragma once

#include "SvMyDesign.hpp"

struct SvMyDesigns
{
	SvMyDesign designs[10];
};
ASSERT_SIZE(SvMyDesigns, 0x5460);
