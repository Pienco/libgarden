#pragma once

#include "IRecept.hpp"

class ITalkRecept : public IRecept
{
public:
	virtual ~ITalkRecept() override;

private:
	u8 data[0x78];
};
ASSERT_SIZE(ITalkRecept, 0x7c);
