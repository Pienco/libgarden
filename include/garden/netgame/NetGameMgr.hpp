#pragma once

#include "ConfirmMachine.hpp"
#include "PacketID.hpp"
#include "StatePacketID.hpp"
#include "PacketQueue.hpp"
#include "AvatarMgr.hpp"
#include "ConnectMgr.hpp"
#include "StageMgr.hpp"
#include "LockMgr.hpp"
#include "JoinMgr.hpp"
#include "LeaveMgr.hpp"
#include "IslandMgr.hpp"
#include "GateMgr.hpp"
#include "FriendListMgr.hpp"

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

		class TransitionMgr
		{
		public:
			enum Mode : u8
			{
				NONE,
				SENDING,
				RECEIVING,
				CLOSED,
			};

		public:
			void* m_pBuffer;
			size_t m_BufferSize;
			PlayerNo m_PlayerEnteringStage;
			PlayerNo m_PlayerExitingStage;
			Mode m_Mode;
		};
		ASSERT_SIZE(TransitionMgr, 0xc);

		class SaveDemoMgr
		{

		public:

			auto& GetState() { return m_State; }

			void OnStartSave(bool endSession);

		private:

			u8 m_State;
			u8 data[0xf];
		};
		ASSERT_SIZE(SaveDemoMgr, 0x10);

		class Mgr8
		{
		public:
			void FUN_00617b70();

		private:
			u8 data[8];
		};
		ASSERT_SIZE(Mgr8, 8);

		PacketQueue* GetPacketQueue() { return &m_PacketQueue; }
		Receiver* GetReceiver() { return &m_Receiver; }
		TransitionMgr* GetTransitionMgr() { return &m_TransitionMgr; }
		AvatarMgr* GetAvatarMgr() { return &m_AvatarMgr; }
		StageMgr* GetStageMgr() { return &m_StageMgr; }
		LockMgr* GetLockMgr() { return &m_LockMgr; }
		JoinMgr* GetJoinMgr() { return &m_JoinMgr; }
		SaveDemoMgr* GetSaveDemoMgr() { return &m_SaveDemoMgr; }
		LeaveMgr* GetLeaveMgr() { return &m_LeaveMgr; }
		Mgr8* GetMgr8() { return &m_Mgr8; }
		IslandMgr* GetIslandMgr() { return &m_IslandMgr; }
		ConnectMgr* GetConnectMgr() { return &m_ConnectMgr; }
		GateMgr* GetGateMgr() { return &m_GateMgr; }
		FriendListMgr* GetFriendListMgr() { return &m_FriendListMgr; }

		void EnterCriticalSection() { m_CriticalSection.Enter(); }
		void ExitCriticalSection() { m_CriticalSection.Exit(); }

		bool IsNewPlayerJoined() const { return m_NewPlayerJoined; }
		void UnsetNewPlayerJoined() { m_NewPlayerJoined = false; }

		void InitEntryOrExit(bool isExit);

		PlayerNo GetMyPlayerNo() const;
		PlayerNo GetMyPlayerNoOrInvalid() const { return m_MyPlayerNo; }
		u8 GetPlayerCount() const;

		bool IsAdmitted(PlayerNo player) const;

		/**
		 * @param skipSelf return false if `player` refers to self
		 * @return whether `player` exists in the net session (not necessarily admitted)
		 */
		bool IsInSession(PlayerNo player, bool skipSelf) const;

		/**
		 * @return whether we have created/joined a net session
		 */
		bool IsInNetSession() const { return m_IsInNetSession; }

		/**
		 * @return whether we have fully joined / been admitted
		 */
		bool IsInNetgame() const { return m_IsInNetgame; }

		bool IsPlayerAssigned() const { return m_IsPlayerAssigned; }

		bool IsMultiPlayer() const;

		bool ConnectRandomMatch();

		bool IsConnectRandomMatch() const
		{
			return m_IsConnectRandomMatch;
		}

		bool IsSessionClosedForIsland() const
		{
			return m_IsSessionClosedForIsland;
		}

		ConnectMgr::Connection GetCurrentConnection() const { return m_CurrentConnection; }

		void FiniNet();

		bool SendPacketBatch(PlayerNo target, const void* const* parts, const size_t* partSizes, size_t partCount, u8 type,
			u32 unknown1, u32 unknown2, u32 unknown3);

		static NetGameMgr* Get() { return s_pInstance; }

	private:
		u8 data0[0x10];
		PacketQueue m_PacketQueue;
		Receiver m_Receiver;
		u8 m_SendMgr[0x2c];
		TransitionMgr m_TransitionMgr;
		AvatarMgr m_AvatarMgr;
		StageMgr m_StageMgr;
		LockMgr m_LockMgr;
		JoinMgr m_JoinMgr;
		SaveDemoMgr m_SaveDemoMgr;
		LeaveMgr m_LeaveMgr;
		Mgr8 m_Mgr8;
		u8 m_Mgr1c[0x1c];
		IslandMgr m_IslandMgr;
		u8 m_BestFriendMgr[0x3f0];
		u8 m_Mgr8b8[0x8b8];
		FriendListMgr m_FriendListMgr;
		u8 data2[0x34];
		ConnectMgr m_ConnectMgr;
		GateMgr m_GateMgr;
		u8 data1[0xb9de];
		ConnectMgr::Connection m_CurrentConnection;
		ConnectMgr::Connection m_LastConnection;
		PlayerNo m_MyPlayerNo;
		u8 unk[3];
		MachineBitTable m_Bits[7];
	public:
		MachineBitTable m_Entry;
		MachineBitTable m_ExistingPlayers;
		MachineBitTable m_Entry2;
	private:
		sead::CriticalSection m_CriticalSection;
		u8 data3[0x10];
		bool m_IsInNetSession;
		bool m_IsInNetgame;
		bool m_IsPlayerAssigned;
		u8 data5[1];
		bool m_IsConnectRandomMatch;
		bool m_IsSessionClosedForIsland;
		u8 unk2[1];
		bool m_NewPlayerJoined;
		u32 data4;

		static NetGameMgr* s_pInstance;
	};
	ASSERT_SIZE(NetGameMgr, 0x132b8);
}
