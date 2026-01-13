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
		u32 m_ConstantID; // PID
		u32 m_VariableID; // CID
		u32 m_ServiceVariableID; // RVCID
		u8 m_UrlType;
		u8 m_NexStreamID;
		u8 m_NexStreamType;
		u8 m_NatMapping;
		u8 m_NatFiltering;
		u8 m_NatFlags;
		u8 m_Probeinit;
		u8 padding;
	};
	static_assert(sizeof(StationLocation) == 0x28);
}
