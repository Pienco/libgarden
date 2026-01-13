#pragma once

#include "common.hpp"
#include "../netgame/netgame.hpp"
#include "Handle.hpp"

namespace fgobj
{
	enum class TreeShakeType : u8
	{
		NONE,
		FRUIT,
		ITEM,
		BEES,
		FRUIT_DIE
	};

	struct Param
	{
		u8 layer : 1;
		bool swingType : 1;
		TreeShakeType treeShakeType : 3;
		bool isCutdown : 1;
		u8 cutCounter : 2;
	};

	struct Action
	{
		enum State : u8
		{
			NONE,
			ONGOING,
			FINISHED,
			CANCELLED,
		};

		SvFgName replace;
		SvFgName fg1;
		SvFgName fg2;
		Position8 pos;
		PlaceType type;
		State state;
		u8 index;
		Param param;
	};
	ASSERT_SIZE(Action, 0x12);

	struct Packet
	{
		enum Type : u8
		{
			BEGIN,
			FINISH,
			CANCEL,
			PLACE,
			UNLOCK_TILE,
			UNLOCK_TILE_ALL,
			REQUEST_PLACE,
			PLACE_AND_SEND,
			LOCK_TILE_DIRECT,
			UNLOCK_TILE_DIRECT,
		};

		Packet();
		void Assign(const Action& action, Type type = BEGIN);
		void Process();
		void Send(netgame::PlayerNo target) const { netgame::EnqueuePacket(0x3a, target, this, sizeof(*this)); }
		void ProcessShakeItemTree();
		
		SvFgName replace;
		SvFgName fg1;
		SvFgName fg2;

		u8 player : 2;
		PlaceType placeType : 6;

		u8 actionIndex : 2;
		Type action : 4;
		u8 unknown : 2;

		Param param;
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

	TreeShakeType GetShake(SvFgName& outItemAfterShake, const SvFgName& shaken);

	Handle BeginAction(PlaceType type, SvFgName& replace, SvFgName& fg1, SvFgName& fg2, u8 x, u8 y, u8 u0, u8 u1, TreeShakeType shakeType, u8 u3, u8 u4);

}
