#pragma once

#include "../sv/SvFgName.hpp"

template<SvFgName::Name FgName>
struct alignas(2) ExchangeBankKeywordFgNameEx 
{
	SvFgName fg {FgName};
};
static_assert(sizeof(ExchangeBankKeywordFgNameEx<SvFgName::EMPTY>) == 0x4);
static_assert(alignof(ExchangeBankKeywordFgNameEx<SvFgName::EMPTY>) == 0x2);
