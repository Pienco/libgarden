#pragma once

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
