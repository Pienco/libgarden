#pragma once

#include "Base.hpp"

class BsMenuBg
{
public:
	static BsMenuBg* Get() { return s_pInstance; }

	void ChangeBg(s32 index);

private:
	static BsMenuBg* s_pInstance;
};
