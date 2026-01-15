#pragma once

#include "../sv/SvIslandShop.hpp"

class IslandData
{
public:

	static IslandData* Get() { return s_pInstance; }

	SvIslandShop& GetShop() { return m_Shop; }

private:
	static IslandData* s_pInstance;

	u8 m_Disposer[0x10];
	SvIslandShop m_Shop;
};
ASSERT_SIZE(IslandData, 0x20);
