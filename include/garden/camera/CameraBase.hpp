#pragma once

#include <nn/math/Vector.hpp>

class CameraBase
{
public:
	virtual ~CameraBase();

private:

	struct Info
	{
		Vector3 position;
		Vector3 unknown;
		Vector2u16 rotation;
		float distance;
	};

	Info m_Data;
};
ASSERT_SIZE(CameraBase, 0x24);
