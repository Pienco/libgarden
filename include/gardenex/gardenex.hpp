#pragma once

#include "detail/Context.hpp"
#include "bs/BsDebugMenu.hpp"

namespace gardenex
{
	using Context = detail::Context;

	inline Context& GetContext()
	{
		return Context::Get();
	}

	inline bool Initialize()
	{
		return Context::Get().Initialize();
	}

	inline bool IsEmulator()
	{
		return GetContext().isEmulator;
	}
}
