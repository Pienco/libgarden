#pragma once

#include "SvFgName.hpp"
#include "../script/Word.hpp"

class SvFgWord
{
public:
	SvFgWord(const SvFgName& fg, void* myDesign = nullptr);

	script::WordFix<33> word;
};
