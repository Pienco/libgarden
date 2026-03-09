#pragma once

#include "Bank.hpp"

class HumanResTextureAnimBank : public Bank<3072u, 1u, false, BankVramConfig<0u, 0u, 0u, 0u, false>>
{
public:

private:
};
ASSERT_SIZE(HumanResTextureAnimBank, 0x14);
