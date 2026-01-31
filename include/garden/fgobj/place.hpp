#pragma once

#include "PlaceRequest.hpp"
#include "../netgame/netgame.hpp"
#include "Handle.hpp"

namespace fgobj
{
	struct Packet
	{
		enum Type : u8
		{
			HANDLE_REQUEST,
			REQUEST_SUCCEEDED,
			REQUEST_FAILED,
			PLACE,
			REQUEST_UNLOCK_UNIT,
			UNLOCK_UNIT_ALL,
			CONFIRM_PENDING_REQUEST,
			PLACE_AND_SEND,
			REQUEST_BEGIN_LOCK_UNIT,
			REQUEST_DONE_UNLOCK_UNIT,
		};

		Packet();
		void Assign(const PlaceRequest& request, Type type = HANDLE_REQUEST);
		void Process();

		void Send(netgame::PlayerNo target = netgame::PlayerNo::TARGET_ALL) const
		{
			netgame::EnqueuePacket(0x3a, target, this, sizeof(*this));
		}

		void ProcessShakeItemTree();
		
		SvFgName replace;
		SvFgName fg1;
		SvFgName fg2;

		u8 player : 2;
		PlaceType placeType : 6;

		u8 requestIndex : 2;
		Type action : 4;
		u8 unknown : 2;

		PlaceParam param;
		std::array<u8, 3> dropOffset;
		stage::Name stage;
		Position8 pos;
		u8 reserved;
	};
	ASSERT_SIZE(Packet, 0x16);

	struct DirectPlacePacket
	{
		void Set(const SvFgName& fg, u8 x, u8 y, stage::Name stage);
		void Place() const;
		void Send() const;
		void PlaceAndSend() const
		{
			Place();
			Send();
		}
		void Send(netgame::PlayerNo target) const { netgame::EnqueuePacket(0x83, target, this, sizeof(*this)); }

		SvFgName fg;
		stage::Name stage;
		Position8 pos;
		u8 pad;
	};
	ASSERT_SIZE(DirectPlacePacket, 8);
}
