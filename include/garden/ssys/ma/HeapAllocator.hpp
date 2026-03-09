#pragma once

#include "Allocator.hpp"

namespace ssys::ma
{
	class HeapAllocator : public Allocator
	{
	public:

	private:
	};
	ASSERT_SIZE(HeapAllocator, 0x8);
}
