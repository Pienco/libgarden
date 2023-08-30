#ifndef AC_ACNPCSPRESETSAN_HPP
#define AC_ACNPCSPRESETSAN_HPP

#include "types.h"

class AcNpcSpResetsan
{

public:

	using Func = void(*)();

	static inline const Func* GetMenuDelegate() { return s_pMenuDelegate; }
	static inline void DisableMenuDelegate() { s_pMenuDelegate = nullptr; }

	

private:

	static Func* s_pMenuDelegate;
	
};

#endif
