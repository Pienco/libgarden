#ifndef BS_BSPIKOHANOBJMGR_HPP
#define BS_BSPIKOHANOBJMGR_HPP

#include "../ac/Actor.hpp"
#include "../g3d/ResourceLoader.hpp"

class BsPikoHanObjMgr : public Base
{

public:

	Actor* GetPikoHanObj()
	{
		return m_pPikoHanObj;
	}

	static BsPikoHanObjMgr* Get() { return s_pInstance; }

private:

	u8 m_Allocator[8];
	g3d::ResourceLoader m_Loader;
	Actor* m_pPikoHanObj;
	u32 m_Data[6];

	static BsPikoHanObjMgr* s_pInstance;
};
ASSERT_SIZE(BsPikoHanObjMgr, 0x140);

#endif