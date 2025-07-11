#ifndef AC_ACNPCSPRESETSAN_HPP
#define AC_ACNPCSPRESETSAN_HPP

#include "common.hpp"

class AcNpcSpResetsan
{

public:

	using Func = void(*)();

	static const Func* GetMenuDelegate() { return s_pMenuDelegate; }
	static void DisableMenuDelegate() { s_pMenuDelegate = nullptr; }

private:

	static Func* s_pMenuDelegate;
	
};

#endif
