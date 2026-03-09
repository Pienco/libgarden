#pragma once

#include "../human/ExchangeModelBank.hpp"
#include "PlayerCapBankKeyword.hpp"
#include "../item/ResLoader.hpp"

class PlayerCapBank : public ExchangeModelBank<31423u, BankVramConfig<2500u, 3u, 12400u, 3u, false>, PlayerCapBankKeyword, item::ResLoader, 2u, true>
{
public:

private:
	u32 unknown;
};
ASSERT_SIZE(PlayerCapBank, 0x4e0);
