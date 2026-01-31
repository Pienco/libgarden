#pragma once

#include "common.hpp"

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

	struct PlaceParam
	{
		u8 layer : 1;
		bool fallDirection : 1;
		TreeShakeType treeShakeType : 3;
		bool isCutdown : 1;
		u8 cutCounter : 2;
	};

	TreeShakeType GetShake(SvFgName& outItemAfterShake, const SvFgName& shaken);
}
