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

		StationConnectionInfo m_LocalConnectionInfo;
		StationConnectionInfo m_RemoteConnectionInfo;
		common::StationAddress m_StationAddress; // TODO - Who does this station belong to???
		StationConnectionInfo* m_ParticipantConnectionInfos;
		u32 m_ParticipantStations[12]; // This is actually a nn::pia::transport::Station*[12], but we'll leave it stubbed
		u32 m_ParticipantSlotCount; // This represents the number of slots initialized, not the actual number of participants connected
		common::CriticalSection m_Section;

		static StationConnectionInfoTable* s_pInstance;
	};
	static_assert(sizeof(StationConnectionInfoTable) == 0x100);

}
