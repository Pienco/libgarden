#pragma once

#include "JmpUnit.hpp"

class JmpBlock
{
public:

private:
	Vector2i m_BlockPos;
	Vector2i m_UnitPos;
	Vector3 m_WPos;
	JmpUnit m_Units[unitBaseNum][unitBaseNum];
};
ASSERT_SIZE(JmpBlock, 0xa1c);
