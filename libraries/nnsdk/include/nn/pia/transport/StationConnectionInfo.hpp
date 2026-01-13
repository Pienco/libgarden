#pragma once

#include <nn/pia/transport/StationLocation.hpp> 

namespace nn::pia::transport
{

	class StationConnectionInfo : public common::RootObject
	{

	public:

		virtual ~StationConnectionInfo();

	private:
		StationLocation m_PublicLocation;
		StationLocation m_PrivateLocation;
	};
	static_assert(sizeof(StationConnectionInfo) == 0x54);

}
