#pragma once

#include "HumanModel.hpp"
#include "../g3d/MaterialAnim.hpp"

class HumanFaceAnimControl : public HumanModel::FaceCtrl
{
public:

private:
	u8 data[0x74];
};
ASSERT_SIZE(HumanFaceAnimControl, 0x94);
