#pragma once

#include "dLoadSplit.hpp"

#include <sead/ObjList.hpp>

class RoModule : public dLoadSplit
{
public:
	virtual ~RoModule() override;

	u32 GetAddress() const { return m_LoadAddr; }
	const char* GetName() const { return m_Name.GetString(); }

private:
	sead::FixedSafeString<32> m_Name;
	u32 m_LoadAddr;
	void* m_Mem;
	u8 m_State;
};
ASSERT_SIZE(RoModule, 0x124);


class DLLRoMgr
{
public:
	static DLLRoMgr* Get() { return s_pInstance; }

	const sead::ObjList<RoModule>& GetLoadedModules() const { return m_LoadedModules; }

private:
	u8 data[0x10];
	sead::FixedObjList<RoModule, 10> m_LoadedModules;

	static DLLRoMgr* s_pInstance;
};
