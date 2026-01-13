#pragma once

#include "InetAddress.hpp"

#include <cstdlib>

namespace nn::pia::common
{
	class StationAddress : public RootObject
	{
	public:
		const InetAddress& GetInetAddress() const { return m_Address; }

		virtual void Trace();

	private:
		InetAddress m_Address;
		u16 unk;
		u16 unk2;
	};
	static_assert(sizeof(StationAddress) == 0x10);
}
