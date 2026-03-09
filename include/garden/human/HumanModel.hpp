#pragma once

#include <nn/types.h>

class HumanModel
{
public:
	class FaceCtrl
	{
	public:

	private:
		u8 data[0x20];
	};
	ASSERT_SIZE(FaceCtrl, 0x20);

private:
};
