#pragma once

#include "../human/ExchangeModelBank.hpp"
#include "../human/ExchangeBankKeywordFgNameEx.hpp"
#include "../item/ResLoader.hpp"

class PlayerBottomsBank : public ExchangeModelBank<17829u, BankVramConfig<500u, 2u, 2800u, 2u, false>, ExchangeBankKeywordFgNameEx<(SvFgName::Name)32765>, item::ResLoader, 2u, true>
{
public:


private:
	u8 unknown;
};
ASSERT_SIZE(PlayerBottomsBank, 0x4ac);
