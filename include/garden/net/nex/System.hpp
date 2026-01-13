#pragma once

#include "Command.hpp"
#include "Impl.hpp"
#include "Error.hpp"

#include <nn/os/CriticalSection.hpp>
#include <nn/pia/types.hpp>

namespace net::nex
{
	class System
	{
	public:
		enum State : u8
		{
			NONE,
			IDLE,
			CONNECTED_LOCAL,
			LOCAL_SESSION,
			LOCAL_ERROR,
			INDEPENDENT,
			CONNECTED_NEX,
			NEX_SESSION,
		};

		auto GetState() const { return m_State; }

		void Cmd_Stub0();

	public:
		void CmdSuccess()
		{
			m_pCmd->SetDone();
			m_pCmd = nullptr;
		};

		void CmdFailed()
		{
			m_pCmd->SetFailed();
			m_pCmd = nullptr;
		}

		nn::os::CriticalSection m_Section;
		Impl m_Impl;
		Command* m_pCmd;
		Error m_Error;
		void (System::*m_StateFn)();
		State m_State;
		void* m_pSender;
		void* m_pCallback;
		nn::pia::StationId m_LocalStationId;
		u32 unk;
		ParticipantInfo m_Participants[4];
		u8 m_ParticipantCount;
		bool m_NeedSendNotification;
		u32 unk2;
	};
	ASSERT_OFFSET(System, System::m_pCallback, 0x2d8);
	ASSERT_OFFSET(System, System::m_LocalStationId, 0x2dc);
	ASSERT_OFFSET(System, System::m_ParticipantCount, 0x328);
	ASSERT_SIZE(System, 0x330);
}
