#ifndef NETGAME_PACKET_HPP
#define NETGAME_PACKET_HPP

#include "item/Item.hpp"
#include "stage/ID.hpp"

namespace netgame
{

	struct DirectItemPlacementPacket
	{
		constexpr DirectItemPlacementPacket(const item::Item& item, u8 x, u8 y, stage::ID stage) :
			item {item}, stage {stage}, x {x}, y{y} {}
		constexpr DirectItemPlacementPacket(stage::ID stage) : stage {stage} {}
		void Set(const item::Item& item, u8 x, u8 y, stage::ID stage);
		void Place() const;
		void Send() const;

		item::Item item;
		stage::ID stage = stage::ID::DUMMY;
		u8 x {};
		u8 y {};
		u8 padding {};
	};
	ASSERT_SIZE(DirectItemPlacementPacket, 8);
}

#endif
