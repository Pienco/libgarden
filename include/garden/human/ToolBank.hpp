#pragma once

#include "ExchangeModelBank.hpp"
#include "ExchangeBankKeywordMyDesignFgNameEx.hpp"
#include "../item/ResLoader.hpp"

class ToolBank : public ExchangeModelBank<24448u, BankVramConfig<736u, 4u, 3824u, 4u, false>, ExchangeBankKeywordMyDesignFgNameEx<SvFgName::EMPTY>, item::ResLoader, 2u, false>
{
public:

private:
	u8 data[0x3d8];
};
ASSERT_SIZE(ToolBank, 0x8a8);
