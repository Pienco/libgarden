#pragma once

#include <nn/pia/common/StationAddress.hpp>

namespace nn::pia::transport
{
	class Station
	{
	public:
		struct IdentificationToken
		{
			u8 data[0x20]; // ASCII
		};
		static_assert(sizeof(IdentificationToken) == 0x20);

		const common::StationAddress& GetAddress() const { return m_Address; }

		virtual void Trace();

	private:
		common::StationAddress m_Address;
	};
}
