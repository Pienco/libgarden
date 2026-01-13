#pragma once

#include <nn/pia/common/RootObject.hpp>

namespace nn::pia::transport
{
	class IdentificationInfo : public common::RootObject
	{

	private:
		// IdentificationToken m_identificationToken;
		// PlayerName m_playerName;
		// u8 m_platformID;
		// u8 _padding[3];
		// u32 m_ackID;
		u8 data[0x4c];
	};
	static_assert(sizeof(IdentificationInfo) == 0x4c);
}
