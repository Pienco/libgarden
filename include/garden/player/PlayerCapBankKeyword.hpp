#pragma once

#include "../human/ExchangeBankKeywordMyDesignFgNameEx.hpp"

struct PlayerCapBankKeyword : ExchangeBankKeywordMyDesignFgNameEx<SvFgName::EMPTY>
{
	u32 unknown;
};
ASSERT_SIZE(PlayerCapBankKeyword, 0x14);
