#pragma once

#include "place.hpp"

namespace fgobj
{
	struct PlaceAction
	{
		enum class State : u8
		{
			NONE,
			PENDING,
			FINISHED,
		};

		SvFgName replace;
		SvFgName fg1;
		SvFgName fg2;
		PlaceParam param;
		netgame::PlayerNo player;
		Position8 pos;
		PlaceType placeType;
		State state;
		std::array<u8, 3> dropOffset;
		stage::Name stage;
	};
	ASSERT_SIZE(PlaceAction, 0x16);

	inline constexpr size_t maxPlaceActions = 32;

	extern std::array<PlaceAction, maxPlaceActions> s_PlaceActions;
}
