#pragma once

#include "MachineBitTable.hpp"

#include <array>

namespace netgame
{
	bool StageTransitionTourResult();

	class LockMgr
	{
	public:

		enum class State : u8
		{
			UNLOCKED,
			LOCKED,
			LOCK_REQUESTED,
			LOCK_PENDING,
		};

		enum class Cmd : u8
		{
			FRIEND_MATCH_ENTRY,
			FRIEND_MATCH_LEAVE,
			SAVE_CONTINUE,
			SAVE_INTERRUPT,
			TOUR_END,
			RANDOM_MATCH_ENTRY,
			RANDOM_MATCH_LEAVE,
			RANDOM_MATCH_START_TOUR,
			COUNT,
			NONE = COUNT,
		};

		enum class Action : u8
		{
			NONE,
			BEGIN,
			WAIT,
			FAIL,
			ACCEPT,
			CANCEL,
			WAIT_DELAY,
			EXEC_CMD,
		};

		enum class RequestIssueState : u8
		{
			NONE,
			BEGIN = 1,
			WAIT = 2,
			FAIL = 3,
			SUCCESS = 4,
		};

		enum class RequestHandleState : u8
		{
			NONE,
			BEGIN = 1,
			LOCK_PLAYER = 2,
			BEGIN_STEP = 3,
			DO_CANCEL = 4,
			CANCELING = 5,
		};

		auto& GetState() { return m_State; }
		auto& GetAction() { return m_Action; }
		auto& GetCmd() { return m_Cmd; }
		auto& GetNextCmds() { return m_NextCmds; }
		auto& GetCmdIssuePlayer() { return m_CmdIssuePlayer; }
		auto& GetRequestCmdBit() { return m_ReqCmdBit; }
		bool ExistsEnteringOrLeavingPlayer() const { return m_SourcePlayer < 4; }

		void Process();

	private:

		void HandleAction();
		void ProcessRequest();
		void ShowTelop();

		void StartHandleNextRequest();

		bool HandleRequestResult(PlayerNo player, bool success);

		PlayerNo GetNextRequestIssuer() const
		{
			for (PlayerNo i = PlayerNo::HOST; i < PlayerNo::MAX_PLAYER_COUNT; i++)
			{
				if (m_ReqIssueState[i] != RequestIssueState::NONE)
					return i;
			}
			return INVALID;
		}

		Cmd m_SuccessfulCmd;
		PlayerNo m_SourcePlayer;
		std::array<RequestIssueState, 4> m_ReqIssueState;
		MachineBitTable m_ReqCmdBit;
		std::array<Cmd, 4> m_NextCmds;
		State m_State;
		Cmd m_NextCmdReq;
		std::array<RequestHandleState, 4> m_ReqHandleState;
		Action m_Action;
		u8 unk6;
		s32 m_WaitPlayerReadyTimer;
		Cmd m_Cmd;
		PlayerNo m_CmdIssuePlayer;
		s32 m_MinimumDelayTimer;
		s32 m_CancelTelopTimer;
		MachineBitTable m_HandleCmdBit;
		bool m_IsActionInProgress;
		bool m_Unlocked;
		bool m_HandleCmdInSinglePlayer; // used to still transition to tour result stage in single player
		u8 unk2[1];
		bool m_ShowingTelop;
		bool m_RequestFailGateClosed;
		bool m_RequestFailNotBestFriends;
		u8 unk7[3];
	};
	ASSERT_SIZE(LockMgr, 0x30);
}
