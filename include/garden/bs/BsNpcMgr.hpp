#pragma once

#include "../ac/AcNpc.hpp"

class BsNpcMgr
{
public:

	struct NpcList
	{
		AcNpc** first;
		AcNpc** last;

		auto** begin() { return first; }
		auto** end() { return last; }
		size_t size() const { return last - first; }
		auto*& operator[](std::size_t i) { return first[i]; }
	};

	static BsNpcMgr* Get() { return s_pInstance; }

	AcNpc** GetFirst() { return m_Npcs.first; }
	AcNpc** GetLast() { return m_Npcs.last; }
	NpcList& GetNpcs() { return m_Npcs; }

private:
	static BsNpcMgr* s_pInstance;

	u8 data[0xeb54];
	NpcList m_Npcs;
};
