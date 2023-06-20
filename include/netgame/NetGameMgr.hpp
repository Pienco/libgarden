#ifndef NETGAME_NETGAMEMGR_HPP
#define NETGAME_NETGAMEMGR_HPP

#include "types.h"

#include "sead/CriticalSection.hpp"

namespace netgame
{

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

		inline Receiver* GetReceiver() { return &m_Receiver; }

		inline void EnterCriticalSection() { m_CriticalSection.Enter(); }
		inline void ExitCriticalSection() { m_CriticalSection.Exit(); }

		u8 GetMyPlayerNo() const;

		

		static inline NetGameMgr* Get() { return s_pInstance; }

	private:

		u8 pad0[0x58];
		Receiver m_Receiver;
		u8 pad1[0x13208];
		sead::CriticalSection m_CriticalSection;

		static NetGameMgr* s_pInstance;
	};
	ASSERT_SIZE(NetGameMgr, 0x1329c);
}

#endif
