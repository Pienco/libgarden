#pragma once

#include "Command.hpp"
#include "System.hpp"

namespace net::nex
{
	class Framework
	{
	public:
		bool CreateOrJoinRandomSession(u32);
		bool Stub0(u32);

		bool ProcessCommand(Command::ID id, const void* param = nullptr);
		Command& GetCommand() { return m_Command; }

	private:
		enum State
		{
			UNINITIALIZED,
			READY,
			LOGGED_IN,
			STATE_3,
		};

		u8 data[0x10];
		nn::os::CriticalSection m_Section;
		System* m_pSystem;
		void* m_pCommandThread;
		void* m_pPacer;
		State m_State;
		u32 unk;
		Command m_Command;
		u32 unk2;
		MatchInfo m_MatchInfo;
		MatchInfo m_MatchInfoThread;
		Error m_Error;
		Error m_ErrorThread;
		u32 m_CommandFlags;
		bool m_Independent;
		u8 m_Unk;
	};
	ASSERT_SIZE(Framework, 0x158);
}
