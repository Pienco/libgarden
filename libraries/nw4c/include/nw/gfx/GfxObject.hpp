#pragma once

#include <nw/os/IAllocator.hpp>
#include <nn/types.h>

namespace nw::gfx
{
	class GfxObject
	{
	public:
		virtual ~GfxObject();
		virtual const void* GetRuntimeTypeInfo() const;

	protected:
		os::IAllocator* m_pAllocator;
	};
	ASSERT_SIZE(GfxObject, 0x8);
}
