#pragma once

#include "BankTablePrivate.hpp"

class BankTableBase : private BankTablePrivate
{
public:

private:
	u16 unknown1;
	u16 unknown2;
};
ASSERT_SIZE(BankTableBase, 0xc);
