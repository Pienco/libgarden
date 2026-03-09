#pragma once

#include "../human/ExchangeModelBank.hpp"
#include "PlayerHeadBankKeyword.hpp"
#include "../g3d/ResourceLoader.hpp"

class PlayerHeadBank : public ExchangeModelBank<25891u, BankVramConfig<1800u, 4u, 6600u, 4u,false>, PlayerHeadBankKeyword, g3d::ResourceLoader, 1u, false>
{
public:

private:
	u32 unknown;
	u8 data[0x278];
};
ASSERT_SIZE(PlayerHeadBank, 0x518);
