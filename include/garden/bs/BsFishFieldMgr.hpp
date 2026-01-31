#pragma once

#include "../ac/Actor.hpp"
#include "../netgame/FishState.hpp"

class BsFishFieldMgr : public Base
{

public:

	struct ListFishEntry
	{
		Actor* actor;
		ListFishEntry* next;
		u8 alloc[0x8];
		u8 unk;
		s32 index;
	};
	ASSERT_SIZE(ListFishEntry, 0x18);

	static BsFishFieldMgr* Get() { return s_pInstance; }

	static constexpr size_t MAX_ENTRY = 8;

	using Angle3u16 = Actor::Angle3u16;
	using FishState = netgame::FishState;
	using FishID = item::FishID;

	FishState* GetNetState(u32 index);
	const FishState* GetNetState(u32 index) const;
	bool IsMyFish(u32 index) const;
	void TakeOwnershipOfNetState(u32 index);

	ListFishEntry* GetNewestEntry() { return m_pNewest; }
	ListFishEntry* GetFreeEntry() { return m_pFree; }
	ListFishEntry* GetEntry(u32 index) { return &m_ListFish[index]; }

	/**
	 * @return always `true`
	 */
	bool CreateFish(FishID id, const Vector3& pos, const Angle3u16& rotation);

private:

	u8 m_Alloc[0x8];
	ListFishEntry* m_pNewest;
	ListFishEntry* m_pFree;
	std::array<ListFishEntry, MAX_ENTRY> m_ListFish;
	u8 data[0x1220];

	static BsFishFieldMgr* s_pInstance;
};
ASSERT_SIZE(BsFishFieldMgr, 0x1304);
