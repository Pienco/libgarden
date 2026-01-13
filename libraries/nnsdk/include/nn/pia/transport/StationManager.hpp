#pragma once

#include "Station.hpp"

namespace nn::pia::transport
{

	class StationManager
	{

	public:

		static StationManager* Get() { return s_pInstance; }

		Result GetStationAddress(common::StationAddress* out, StationId id) const;

	private:

		static StationManager* s_pInstance;
	};

}
