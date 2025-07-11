#ifndef NETGAME_NETGAMEMGR_HPP
#define NETGAME_NETGAMEMGR_HPP

#include "netgame/ConfirmMachine.hpp"
#include "netgame/PacketID.hpp"
#include "netgame/StatePacketID.hpp"

#include "stage/ID.hpp"
#include "stage/TourID.hpp"

#include "util/enum.hpp"
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

		class FieldControlMgr
		{

		public:

			struct PlayerStageUpdatePacket
			{
				void Set(PlayerNo player, bool updateStage, stage::ID stage, bool updateControl, bool own, PlayerNo receiver = PlayerNo::INVALID);

				u16 value;
			};

			void SetStage(PlayerNo player, stage::ID stage);
			void UpdateFieldControl(PlayerNo player, bool own);

			u8 GetPlayerCount(stage::ID stage) const { return m_Stages.GetPlayerCount(stage); }
			PlayerNo GetTransitioningPlayer() const;

		private:

			struct PlayerStages
			{
				u8 GetPlayerCount(stage::ID stage) const;

				stage::ID stages[netgame::MAX_PLAYER_COUNT];
				u8 ctrl;
			};

			u8 m_State;
			PlayerStages m_Stages;
			u8 data[0x1e];
		};
		ASSERT_SIZE(FieldControlMgr, 0x24);

		class MatchingMgr
		{
		
		public:

			auto& GetState() { return m_State; }
			auto& GetAction() { return m_Action; }
			auto& GetTransition() { return m_Transition; }
			auto& GetNextTransitions() { return m_NextTransitions; }
			auto& GetTransitionPlayer() { return m_TransitionPlayer; }
			auto& GetRequestTransitionBit() { return m_ReqTransitionBit; }
			bool ExistsEnteringOrLeavingPlayer() const { return m_EnteringOrLeavingPlayer < 4; }

		private:

			u8 unk;
			PlayerNo m_EnteringOrLeavingPlayer;
			u8 m_NextStates[4];
			MachineBitTable m_ReqTransitionBit;
			std::array<u8, 4> m_NextTransitions;
			u8 m_State;
			u8 m_NextTransitionReq;
			u8 m_ReqProcessingState[4];
			u8 m_Action;
			u8 unk6;
			s32 m_SomeTimer;
			u8 m_Transition;
			PlayerNo m_TransitionPlayer;
			u8 unk7[0x16];
		};
		ASSERT_SIZE(MatchingMgr, 0x30);

		class ConnectMgr
		{
		
		public:

			u8& GetState() { return m_State; }

		private:
			u8 m_State;
			u8 data[0x17];
		};
		ASSERT_SIZE(ConnectMgr, 0x18);

		class Unknown1
		{
		
		public:

			bool Check(u8 index);

		private:

			u8 data[0xc];

		};
		ASSERT_SIZE(Unknown1, 0xc);

		class IslandMgr
		{
		
		public:

			using TourID = stage::TourID;

			enum TourDeskSelection : u8
			{
				TOUR,
				ISLAND_LEAVE,
				RANDOM_MATCH_TOUR,
			};

			auto GetState() const { return m_State; }
			auto& GetState() { return m_State; }
			auto GetTour() const { return m_TourID; }
			auto& GetTour() { return m_TourID; }
			auto GetLeavingPlayer() const { return m_LeavingPlayer; }
			auto GetTourDeskOptionChooser() const { return m_TourDeskOptionChooser; }
			auto& GetTourDeskOptionChooser() { return m_TourDeskOptionChooser; }
			auto& GetTourDeparters() { return m_PlayersThatDepartForTour; }
			auto& GetTourStayers() { return m_PlayersThatDoNotDepartForTour; }

			/**
			 * @return `false` iff invalid tour id
			 */
			bool ChooseTour(TourID tour);

			void UpdatePlayerTourSplit(u8 depart, u8 stay);

			/**
			 * @return always `true`
			 */
			bool RetireFromIsland();

			bool CanRetireRandomMatch();
			bool RequestRandomMatchSeeOff();
			bool IsRetiringRandomMatch();
			void ConfirmLeaveSelf();

		private:
			u8 m_State;
			TourDeskSelection m_TourDeskSelection;
			TourID m_TourID;
			PlayerNo m_LeavingPlayer;
			PlayerNo m_TourDeskOptionChooser;
			MachineBitTable m_PlayersThatDepartForTour;
			MachineBitTable m_PlayersThatDoNotDepartForTour;
			u8 m_Data[0x143];
		};
		ASSERT_SIZE(IslandMgr, 0x14c);

		Receiver* GetReceiver() { return &m_Receiver; }
		TransitionMgr* GetTransitionMgr() { return &m_TransitionMgr; }
		FieldControlMgr* GetFieldControlMgr() { return &m_FieldControlMgr; }
		MatchingMgr* GetMatchingMgr() { return &m_MatchingMgr; }
		ConnectMgr* GetConnectMgr() { return &m_ConnectMgr; }
		IslandMgr* GetIslandMgr() { return &m_IslandMgr; }
		Unknown1* GetUnk1() { return &m_Unk1; }

		void EnterCriticalSection() { m_CriticalSection.Enter(); }
		void ExitCriticalSection() { m_CriticalSection.Exit(); }

		bool IsNewPlayerJoined() const { return m_NewPlayerJoined; }
		void UnsetNewPlayerJoined() { m_NewPlayerJoined = false; }

		void InitEntryOrExit(bool isExit);

		PlayerNo GetMyPlayerNo() const;
		u8 GetPlayerCount() const;

		static NetGameMgr* Get() { return s_pInstance; }

	private:

		u8 data0[0x58];
		Receiver m_Receiver;
		u8 m_SyncMgr[0x2c];
		TransitionMgr m_TransitionMgr;
		u8 m_AvatarMgr[0x110];
		FieldControlMgr m_FieldControlMgr;
		MatchingMgr m_MatchingMgr;
		ConnectMgr m_ConnectMgr;
		u8 m_Mgr10[0x10];
		u8 m_Mgr2540[0x2540];
		u8 m_Mgr8[8];
		u8 m_Mgr1c[0x1c];
		IslandMgr m_IslandMgr;
		u8 data2[0x4f88];
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
