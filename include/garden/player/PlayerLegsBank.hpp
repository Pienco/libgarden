#pragma once

#include "../human/ExchangeModelBank.hpp"
#include "../human/ExchangeBankKeywordMyDesignFgNameEx.hpp"
#include "../item/ResLoader.hpp"

class PlayerLegsBank : public ExchangeModelBank<17879u, BankVramConfig<700u, 2u, 3600u, 2u, false>, ExchangeBankKeywordMyDesignFgNameEx<(SvFgName::Name)32765>, item::ResLoader, 2u, true>
{
public:

private:
	u32 unknown;
};
ASSERT_SIZE(PlayerLegsBank, 0x4d4);
