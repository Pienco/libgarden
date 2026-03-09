#pragma once

#include "../human/ExchangeModelBank.hpp"
#include "../human/ExchangeBankKeywordFgNameEx.hpp"
#include "../item/ResLoader.hpp"

class PlayerAcceBank : public ExchangeModelBank<13772u, BankVramConfig<300u, 2u, 2000u, 2u, false>, ExchangeBankKeywordFgNameEx<(SvFgName::Name)32766>, item::ResLoader, 1u, true>
{
public:

};
ASSERT_SIZE(PlayerAcceBank, 0x280);
