#pragma once

#include "types.hpp"

class JmpUnit
{
public:

private:
	u16 m_Heights[4];
	u8 m_Attribute;
	u8 m_Flags;
};
ASSERT_SIZE(JmpUnit, 0xa);
