#pragma once

#include "PlayerNo.hpp"

namespace netgame
{
	class PacketQueue
	{
	public:

		auto& GetLeavingPlayer() { return m_LeavingPlayer; }

		bool IsClosed() const { return m_IsClosed; }

		void BeginPacket();
		void AddPacketData(const void* data, size_t size);
		void EndPacket(u8 id, PlayerNo target);

	private:
		void* m_pBuffer;
		s32 m_Front;
		s32 m_Back;
		void* m_pReceiveStateBuffer;
		void* m_pSendStateBuffer;
		size_t m_SendStateBufferSize;
		bool* m_pShouldSendStateUpdate;
		s32 m_Counter[4];
		PlayerNo m_LeavingPlayer;
		s32 m_Counter2[4];
		s32 m_Tick;
		bool m_IsClosed;
	};
	ASSERT_SIZE(PacketQueue, 0x48);
}
