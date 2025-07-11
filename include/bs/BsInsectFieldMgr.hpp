#ifndef BS_BSINSECTFIELDMGR_HPP
#define BS_BSINSECTFIELDMGR_HPP

#include "ac/Actor.hpp"
#include "netgame/InsectState.hpp"

class BsInsectFieldMgr : public Base
{

public:

	struct ListInsectEntry
	{
		Actor* actor;
		ListInsectEntry* next;
		u8 alloc[0x8];
		u8 unk;
		s32 index;
	};
	ASSERT_SIZE(ListInsectEntry, 0x18);

	struct InsectResource
	{
		u8 data[0x144];
	};
	ASSERT_SIZE(InsectResource, 0x144);

	static BsInsectFieldMgr* Get() { return s_pInstance; }

	static constexpr size_t MAX_ENTRY = 12;

	using Angle3u16 = Actor::Angle3u16;
	using InsectState = netgame::InsectState;
	using InsectID = item::InsectID;

	InsectState* GetNetState(u32 index) { return &m_NetInsectStates[index]; }
	const InsectState* GetNetState(u32 index) const { return &m_NetInsectStates[index]; }

	ListInsectEntry* GetNewestEntry() { return m_pNewest; }
	ListInsectEntry* GetFreeEntry() { return m_pFree; }
	ListInsectEntry* GetEntry(u32 index) { return &m_ListInsects[index]; }

	void CreateInsect(InsectID id, const Vector3& pos, const Angle3u16& rotation);

private:

	u8 m_Alloc[0x8];
	ListInsectEntry* m_pNewest;
	ListInsectEntry* m_pFree;
	InsectResource* m_pRes1;
	InsectResource* m_pRes2;
	std::array<InsectResource, MAX_ENTRY> m_Resources;
	std::array<InsectResource, 2> m_Resources2;
	s32 unk1;
	Vector3 m_DefaultPosition;
	u8 data[0x2c];
	std::array<ListInsectEntry, MAX_ENTRY> m_ListInsects;
	std::array<ListInsectEntry, 2> m_ListInsects2;
	std::array<InsectState, MAX_ENTRY> m_NetInsectStates;
	s32 unk;

	static BsInsectFieldMgr* s_pInstance;
};
ASSERT_SIZE(BsInsectFieldMgr, 0x13bc);

#endif
