#pragma once

#include "../sv/SvFgName.hpp"
#include "../script/Word.hpp"

namespace item
{
	const struct ParamItemEntry* GetParamItemEntry(const SvFgName& item);
	void GetName(script::WordPtr* out, const SvFgName& item, void* myDesign = nullptr);
	u16 GetIconID(const SvFgName& item);
	const char* GetIconName(const SvFgName& item);
	s32 GetIndex(const SvFgName& item);
	u32 ToInsectFishID(const SvFgName& item);
}
