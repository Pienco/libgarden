#pragma once

#include "Actor.hpp"
#include "../bs/BsTelop.hpp"
#include "../tour/TourName.hpp"
#include "../netgame/netgame.hpp"
#include "../npc/NpcAssistPacket.hpp"

class AcNpcSpTourDesk
{
public:
	enum class TripType : u8
	{
		NONE,
		TOUR,
		RETURN_TO_TOWN,
	};

	struct AssistPacketData
	{
		enum Type : u8
		{
			QUEUE_TOUR,
			QUEUE_RETURN_TO_TOWN,
			CANCEL_TRIP,
			REQUEST_CANCEL_TRIP,
			REQUEST_FORCE_LEAVE,
			CANCEL_FORCE_LEAVE_REQUEST,
			SET_CURRENT_FORCE_LEAVE_PLAYER,
		};

		Type type;
		TourName tour = static_cast<TourName>(0xff);
		netgame::PlayerNo targetPlayer = netgame::PlayerNo::INVALID;
		bool kappeiSong = false;
	};
	ASSERT_SIZE(AssistPacketData, 0x4);

	struct AssistPacket : NpcAssistPacket
	{
		AssistPacketData data;
	};
	ASSERT_SIZE(AssistPacket, 0x5);

	static void SendAssistPacket(netgame::PlayerNo target, const AssistPacketData& data);

	static TripType& GetQueuedTrip()
	{
		return s_RequestInfo.queuedTrip;
	}

	static bool IsTourQueued()
	{
		return s_RequestInfo.queuedTrip == TripType::TOUR;
	}

	static bool IsReturnToTownQueued()
	{
		return s_RequestInfo.queuedTrip == TripType::RETURN_TO_TOWN;
	}

	static TourName& GetQueuedTour()
	{
		return s_RequestInfo.queuedTour;
	}

	static netgame::PlayerNo& GetTripRequestPlayer()
	{
		return s_RequestInfo.tripRequestPlayer;
	}
	
	static netgame::PlayerNo& GetForceLeavePlayer()
	{
		return s_RequestInfo.forceLeavePlayer;
	}

	static u8& GetForceLeaveRequestBit()
	{
		return s_RequestInfo.forceLeaveRequestBit;
	}

	static bool IsForceLeaveRequest()
	{
		return s_RequestInfo.forceLeaveRequestBit != 0;
	}

	static bool& IsRequestKappeiSong()
	{
		return s_RequestInfo.kappeiSong;
	}

	static void QueueTourCore(netgame::PlayerNo requester, TourName tour)
	{
		GetTripRequestPlayer() = requester;
		GetQueuedTrip() = TripType::TOUR;
		GetQueuedTour() = tour;
		BsTelop::ShowTourTelop(BsTelop::TOUR_DEPARTING_SOON, tour);

		if (netgame::GetNetgameType() == netgame::Type::RANDOM_MATCH)
			netgame::RequestCloseGateRandomMatch(netgame::GateMgr::RANDOM_MATCH_TOUR);
	}

	static void CancelTripSelf()
	{
		if (GetQueuedTrip() == TripType::TOUR)
		{
			BsTelop::ShowTourTelop(BsTelop::TOUR_CANCEL, GetQueuedTour());
			if (netgame::GetNetgameType() == netgame::Type::RANDOM_MATCH)
				netgame::RequestOpenGateRandomMatch(netgame::GateMgr::RANDOM_MATCH_TOUR);
		}
		else BsTelop::ShowTelop(BsTelop::RETURN_TO_TOWN_CANCELED);

		GetQueuedTrip() = TripType::NONE;
		GetQueuedTour() = static_cast<TourName>(0xff);
		GetTripRequestPlayer() = netgame::PlayerNo::INVALID;
		IsRequestKappeiSong() = false;

		SendAssistPacket(netgame::PlayerNo::TARGET_ALL, {AssistPacketData::CANCEL_TRIP});
	}

private:
	struct RequestInfo
	{
		TripType queuedTrip;
		TourName queuedTour;
		netgame::PlayerNo tripRequestPlayer;
		netgame::PlayerNo forceLeavePlayer;
		u8 forceLeaveRequestBit;
		bool kappeiSong;
	};
	ASSERT_SIZE(RequestInfo, 6);

	static RequestInfo s_RequestInfo;
};
