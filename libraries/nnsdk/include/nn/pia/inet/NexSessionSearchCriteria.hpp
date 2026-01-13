#pragma once

#include <nn/pia/session/SessionSearchCriteria.hpp>

namespace nn::pia::inet
{
	class NexSessionSearchCriteria : public session::SessionSearchCriteria
	{
	public:
		NexSessionSearchCriteria();

		virtual ~NexSessionSearchCriteria() override {}

		void SetGameMode(u32 value);
		void SetSessionType(u8 value) { m_SessionType = value; }
		void SetMinParticipants(u16 value);
		void SetMaxParticipants(u16 value);
		void SetOpenedOnly(bool value);
		void SetVacantOnly(bool value);
		void SetAttribute(u32 index, u32 value);

	private:
		u8 data[0x10];
		u8 m_SessionType;
		u8 data2[0x9f4];
	};
	ASSERT_SIZE(NexSessionSearchCriteria, 0xa18);
}