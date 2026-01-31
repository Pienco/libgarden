#pragma once

#include <nn/pia/transport/Protocol.hpp>

namespace nn::pia::transport
{
	class ReliableProtocol : public Protocol
	{
	public:

	private:
		StationIndex m_LocalStation;
		u32 m_MaxStations;
		void* m_pSlidingWindows;
		size_t m_CurrentSlidingWindowIndex;
	};
	ASSERT_SIZE(ReliableProtocol, 0x24);
};
