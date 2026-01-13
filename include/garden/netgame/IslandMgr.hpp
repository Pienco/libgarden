#pragma once

#include "MachineBitTable.hpp"
#include "../tour/TourName.hpp"

namespace netgame
{
	class IslandMgr
	{
	public:
		using TourName = ::TourName;

		enum TourDeskSelection : u8
		{
			TOUR,
			ISLAND_LEAVE,
			RANDOM_MATCH_TOUR,
		};

		auto GetState() const { return m_State; }
		auto& GetState() { return m_State; }
		auto GetTour() const { return m_TourName; }
		auto& GetTour() { return m_TourName; }
		auto GetLeavingPlayer() const { return m_LeavingPlayer; }
		auto GetTourDeskOptionChooser() const { return m_TourDeskOptionChooser; }
		auto& GetTourDeskOptionChooser() { return m_TourDeskOptionChooser; }
		auto& GetTourDeparters() { return m_PlayersThatDepartForTour; }
		auto& GetTourStayers() { return m_PlayersThatDoNotDepartForTour; }

		/**
		 * @return `false` iff invalid tour id
		 */
		bool ChooseTour(TourName tour);

		void UpdatePlayerTourSplit(u8 depart, u8 stay);

		void StartTourRandomMatch();

		void StartTourDeskArrivalAfterTour();

		/**
		 * @return always `true`
		 */
		bool DepartForIsland();

		/**
		 * @return always `true`
		 */
		bool StartFindRandomMatch();

		/**
		 * @return `-1`: error `0`: not done `1`: done
		 */
		s32 GetRandomMatchingResult();

		/**
		 * @return always `true`
		 */
		bool EndSeaDepartureDemo(bool stageChanged);

		/**
		 * @return always `true`
		 */
		bool RetireFromIsland();

		enum LeaveRandomMatchMode : u8
		{
			RETIRE, // we are leaving
			SEE_OFF, // someone else is leaving
		};

		void LeaveRandomMatch(LeaveRandomMatchMode mode);

		bool CanRetireRandomMatch();
		bool RequestRandomMatchSeeOff();
		bool IsRetiringRandomMatch();
		void ConfirmLeaveSelf();

		bool IsSelfDepartingForTour() const 
		{
			return m_IsSelfDepartingForTour;
		}

	private:
		u8 m_State;
		TourDeskSelection m_TourDeskSelection;
		TourName m_TourName;
		PlayerNo m_LeavingPlayer;
		PlayerNo m_TourDeskOptionChooser;
		MachineBitTable m_PlayersThatDepartForTour;
		MachineBitTable m_PlayersThatDoNotDepartForTour;
		u8 m_Data[0x13b];
		bool m_IsSelfDepartingForTour;
		u8 m_Data2[7];
	};
	ASSERT_SIZE(IslandMgr, 0x14c);

	enum class TourState : u8
	{
		NONE,
		TOUR_SET,
		RETURN_TO_TOWN,
	};

	inline bool IsTourSet()
	{
		extern TourState s_TourState;
		return s_TourState == TourState::TOUR_SET;
	}

	inline bool IsReturnToTownChosen()
	{
		extern TourState s_TourState;
		return s_TourState == TourState::RETURN_TO_TOWN;
	}

	inline PlayerNo GetTourRequestPlayerNo()
	{
		extern PlayerNo s_TourRequestPlayerNo;
		return s_TourRequestPlayerNo;
	}

	inline IslandMgr::TourName GetTour()
	{
		extern IslandMgr::TourName s_SetTourID;
		return s_SetTourID;
	}

	inline bool IsForceLeaveRequest()
	{
		extern u8 s_ForceLeaveRequest;
		return s_ForceLeaveRequest != 0;
	}
}
