#pragma once

#include <nn/pia/transport/StationConnectionInfo.hpp>
#include <nn/pia/common/CriticalSection.hpp>

namespace nn::pia::transport
{

	class StationConnectionInfoTable
	{

	public:

		static StationConnectionInfoTable* Get() { return s_pInstance; }

		virtual ~StationConnectionInfoTable();

	private:

		u8 data[0xf4];
		common::CriticalSection m_Section;

		static StationConnectionInfoTable* s_pInstance;
	};
	static_assert(sizeof(StationConnectionInfoTable) == 0x100);

}
