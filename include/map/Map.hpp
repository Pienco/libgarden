#ifndef MAP_MAP_HPP
#define MAP_MAP_HPP

#include "map/ItemMap.hpp"
#include "map/ID.hpp"
#include "math/Vector.hpp"

namespace map
{
	inline ID GetCurrent()
	{
		extern ID s_Current;
		return s_Current;
	}
	inline bool IsCurrent(map::ID id) { return id == GetCurrent(); }

	ItemMap* GetItemMap(ItemMapID id);


	s32 GetRandom(s32 end);
}

#endif
