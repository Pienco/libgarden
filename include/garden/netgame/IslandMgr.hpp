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
			LEAVE_ISLAND,
			NONE,
		};

		auto GetState() const { return m_State; }
		auto& GetState() { return m_State; }
		auto GetTour() const { return m_TourName; }
		auto& GetTour() { return m_TourName; }
		auto GetLeavingPlayer() const { return m_LeavingPlayer; }
		auto GetTripRequestPlayer() const { return m_TripRequestPlayer; }
		auto& GetTripRequestPlayer() { return m_TripRequestPlayer; }
		auto& GetChosenTrip() { return m_ChosenTrip; }
		auto& GetTourDeparters() { return m_PlayersThatDepartForTour; }
		auto& GetTourStayers() { return m_PlayersThatDoNotDepartForTour; }

		/**
		 * @return `false` iff invalid tour id
		 */
		bool ChooseTour(TourName tour);

		/**
		 * @return always `true`
		 */
		bool CancelTrip();

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
		TourDeskSelection m_ChosenTrip;
		TourName m_TourName;
		PlayerNo m_LeavingPlayer;
		PlayerNo m_TripRequestPlayer;
		MachineBitTable m_PlayersThatDepartForTour;
		MachineBitTable m_PlayersThatDoNotDepartForTour;
		u8 m_Data[0x13b];
		bool m_IsSelfDepartingForTour;
		u8 m_Data2[7];
	};
	ASSERT_SIZE(IslandMgr, 0x14c);
}
