#pragma once

#include "PlaceParam.hpp"
#include "Handle.hpp"

namespace fgobj
{
	struct PlaceRequest
	{
		enum State : u8
		{
			NONE,
			IN_PROGRESS,
			SUCCESS,
			FAIL,
		};

		SvFgName replace;
		SvFgName fg1;
		SvFgName fg2;
		Position8 pos;
		PlaceType type;
		State state;
		u8 index;
		PlaceParam param;
	};
	ASSERT_SIZE(PlaceRequest, 0x12);

	inline constexpr size_t maxPlaceRequests = 4;

	Handle RequestPlace(PlaceType type, const SvFgName& replace, const SvFgName& fg1, const SvFgName& fg2, u8 x, u8 z,
		u8 layer = 0, u8 treeFallDir = 0, TreeShakeType shakeType = TreeShakeType::NONE, bool fellTree = false, u8 treeCutCount = 0);

	PlaceRequest::State GetPlaceRequestState(Handle handle);
}
