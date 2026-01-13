#pragma once

#include <nn/types.h>

class SvStepInner
{
public:

private:
	u8 data[0x38];
};
ASSERT_SIZE(SvStepInner, 0x38);
