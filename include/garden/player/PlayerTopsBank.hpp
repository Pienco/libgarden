#pragma once

#include "../human/ExchangeModelBank.hpp"
#include "../human/ExchangeBankKeywordMyDesignFgNameEx.hpp"
#include "../item/ResLoader.hpp"

class PlayerTopsBank : public ExchangeModelBank<32891u, BankVramConfig<2800u, 2u, 8800u, 2u, false>, ExchangeBankKeywordMyDesignFgNameEx<(SvFgName::Name)32765>, item::ResLoader, 2u, true>
{
public:

private:
	u32 unknown;
};
ASSERT_SIZE(PlayerTopsBank, 0x4d4);
