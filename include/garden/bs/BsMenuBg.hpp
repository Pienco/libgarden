#ifndef BS_BSMENUBG_HPP
#define BS_BSMENUBG_HPP

#include "Base.hpp"

class BsMenuBg
{

public:

	void ChangeBg(s32 index);

	static BsMenuBg* Get() { return s_pInstance; }

private:

	static BsMenuBg* s_pInstance;
};

#endif
