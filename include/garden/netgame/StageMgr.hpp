#pragma once

#include "PlayerNo.hpp"
#include "../stage/Name.hpp"

#include <array>

namespace netgame
{
	class StageMgr
	{
	public:
		struct PlayerStageUpdatePacket
		{
			void Set(PlayerNo player, bool updateStage, stage::Name stage, bool updateControl, bool control, PlayerNo receiver = PlayerNo::INVALID);

			u16 value;
		};

		void SetStage(PlayerNo player, stage::Name stage);
		void UpdateStageControl(PlayerNo player, bool control);

		u8 GetPlayerCount(stage::Name stage) const { return m_Stages.GetPlayerCount(stage); }
		stage::Name GetStage(PlayerNo player) const { return m_Stages.GetStage(player); }
		u8 GetControlBit() const { return m_Stages.ctrl; }
		PlayerNo GetTransitioningPlayer() const;

		const auto& GetNextStages() const { return m_Transitions.nextStages; }

		bool FUN_0075f464() const;

		bool IsBusy() const { return m_State != 0; }

	private:
		struct PlayerStages
		{
			u8 GetPlayerCount(stage::Name stage) const;
			stage::Name GetStage(PlayerNo player) const;

			stage::Name stages[netgame::MAX_PLAYER_COUNT];
			u8 ctrl;
		};

		struct Transitions
		{
			std::array<stage::Name, PlayerNo::MAX_PLAYER_COUNT> nextStages;
			std::array<u8, PlayerNo::MAX_PLAYER_COUNT> slots;
		};

		u8 m_State;
		PlayerStages m_Stages;
		Transitions m_Transitions;
		u8 data[0x16];
	};
	ASSERT_SIZE(StageMgr, 0x24);
}
