#pragma once

#include "../Allocator.hpp"

namespace ssys::ma::lyt
{
	Allocator* GetAllocator();
	Allocator* GetDeviceAllocator();
}
