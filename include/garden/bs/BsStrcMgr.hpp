#pragma once

class BsStrcMgr
{
public:
	static BsStrcMgr* Get() { return s_pInstance; }

private:
	static BsStrcMgr* s_pInstance;
};
