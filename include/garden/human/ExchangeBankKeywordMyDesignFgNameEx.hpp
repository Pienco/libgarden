#pragma once

#include "../sv/SvFgName.hpp"

template<SvFgName::Name FgName>
struct ExchangeBankKeywordMyDesignFgNameEx
{
	SvFgName fg {FgName};
	u32 unknown0 = 0;
	u32 unknown1 = 0;
	u8 unknown2 = 200;
	u8 unknown3 = 200;
	u8 unknown4 = 0;
};
static_assert(sizeof(ExchangeBankKeywordMyDesignFgNameEx<(SvFgName::Name)32765>) == 0x10);
