#pragma once

#include <nn/pia/common/StationAddress.hpp>

namespace nn::pia::transport
{
	class StationLocation
	{
	public:

		virtual ~StationLocation();

	private:
		common::StationAddress m_StationAddress;
		u8 data[0x18];
	};
	static_assert(sizeof(StationLocation) == 0x28);
}
