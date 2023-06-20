#ifndef SSYS_MA_LYT_ARCRESOURCEACCESSORVRAM_HPP
#define SSYS_MA_LYT_ARCRESOURCEACCESSORVRAM_HPP

#include "nw/lyt/ArcResourceAccessor.hpp"

namespace ssys::ma::lyt
{

	class ArcResourceAccessorVRAM final : public nw::lyt::ArcResourceAccessor
	{

	};
	ASSERT_SIZE(ArcResourceAccessorVRAM, 0x13c);
}

#endif
