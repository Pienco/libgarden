#pragma once

#include "RootObject.hpp"

namespace nn::pia::common
{
	class InetAddress : public RootObject
	{
	public:

		constexpr u32 GetAddress() const { return m_Address; }
		constexpr u16 GetPort() const { return m_Port; }

	private:
		u32 m_Address {};
		u16 m_Port {};
	};
	static_assert(sizeof(InetAddress) == 0x8);
}
