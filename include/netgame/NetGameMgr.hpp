#ifndef NETGAME_NETGAMEMGR_HPP
#define NETGAME_NETGAMEMGR_HPP

#include "types.h"

#include "sead/CriticalSection.hpp"

namespace netgame
{

	enum PlayerNo : u8
	{
		PLAYER_0,
		PLAYER_1,
		PLAYER_2,
		PLAYER_3,
		INVALID = 4,
		MY_NO = 4,
		TARGET_ALL = 4,
	};

	class NetGameMgr
	{

	public:

		class Receiver
		{

		public:

			static constexpr size_t RECEIVE_BUFFER_SIZE = 0x16802;

			void* GetBuffer(u8 no);
			const void* GetPacket(u8 from);
			void SetIsEnabled(u8 no, bool set);
			void SetWasHandled(u8 no, bool set);
		
		private:
			
			void* m_pBuffer;
			u8 data[0x1c];
		};
		ASSERT_SIZE(Receiver, 0x20);

		class Unknown1
		{
		
		public:

			bool Check(u8 index);

		private:

			u8 data[0xc];

		};
		ASSERT_SIZE(Unknown1, 0xc);

		Receiver* GetReceiver() { return &m_Receiver; }
		Unknown1* GetUnk1() { return &m_Unk1; }

		void EnterCriticalSection() { m_CriticalSection.Enter(); }
		void ExitCriticalSection() { m_CriticalSection.Exit(); }

		bool IsNewPlayerJoined() const { return m_NewPlayerJoined; }
		void UnsetNewPlayerJoined() { m_NewPlayerJoined = false; }

		PlayerNo GetMyPlayerNo() const;

		static NetGameMgr* Get() { return s_pInstance; }

	private:

		u8 data0[0x58];
		Receiver m_Receiver;
		u8 data2[0x77fc];
		Unknown1 m_Unk1;
		u8 data1[0xba00];
		sead::CriticalSection m_CriticalSection;
		u8 data3[0x17];
		bool m_NewPlayerJoined;
		u32 data4;

		static NetGameMgr* s_pInstance;
	};
	ASSERT_SIZE(NetGameMgr, 0x132b8);
}

#endif
