#pragma once

#include "CameraBase.hpp"

class CameraGame : public CameraBase
{
public:
	static CameraGame* GetInstance() { return s_pInstance; }

private:
	static CameraGame* s_pInstance;
};
