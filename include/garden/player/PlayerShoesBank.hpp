#pragma once

#include "../human/ExchangeModelBank.hpp"
#include "../human/ExchangeBankKeywordFgNameEx.hpp"
#include "../item/ResLoader.hpp"

class PlayerShoesBank : public ExchangeModelBank<17703u, BankVramConfig<600u, 2u, 3600u, 2u, false>, ExchangeBankKeywordFgNameEx<(SvFgName::Name)32766>, item::ResLoader, 2u, true>
{
public:

private:
};
ASSERT_SIZE(PlayerShoesBank, 0x4a8);
