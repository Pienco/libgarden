#pragma once

#include "../human/Bank.hpp"
#include "../g3d/ResourceLoader.hpp"

class PlayerFaceBank : public Bank<40543u, 1u, true, EmptyBankVramConfig>
{
public:

private:
	g3d::ResourceLoader m_ResourceLoader;
};
ASSERT_SIZE(PlayerFaceBank, 0x11c);
