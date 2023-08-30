#ifndef BS_BSMENUMGR_HPP
#define BS_BSMENUMGR_HPP

#include "bs/MenuBase.hpp"
#include "state/Mode.hpp"
#include "bs/BsMenuTab.hpp"
#include "bs/BsMenuBg.hpp"
#include "bs/BsHandCursor.hpp"

class BsMenuMgr : public Base, state::Mode<BsMenuMgr>
{

public:

	enum Menu : u8
	{
		COUNT = 0x8c,
	};

	static bool CanOpenMenuThink();
	static inline MenuBase* GetMenuProcess() { return s_pInstance->m_pProcess; }
	static bool CreateMenuProcess(Menu menu, u8 param = 1);
	static inline void DisableHandCursor()
	{
		if (s_pInstance->m_HandMode == 1)
		{
			if (s_pInstance->m_pBsHandCursor != nullptr)
				s_pInstance->m_pBsHandCursor->Disable();
			s_pInstance->m_HandMode = 0;
		}
	} 
	
private:

	s32 m_Unk[2];
	u8 m_HandMode;
	INSERT_PAD(3);
	u8 m_Controller[0x190];
	s32 m_Unk1;
	class BsMenuMain* m_pBsMenuMain;
	BsMenuBg* m_pBsMenuBg;
	BsMenuTab* m_pBsMenuTab;
	MenuBase* m_pProcess;
	class BsMenuRoomMgr* m_pRoomMgr;
	s32 m_Unk2[2];
	BsHandCursor* m_pBsHandCursor;
	class BsMenuRandomHeadsUp* m_pBsMenuRandomHeadsUp;
	u8 m_HandGrabTimer;
	u8 m_CurrentActionNodeIndex;
	s32 m_Unk3[2];
	bool m_IsCancel;

	static BsMenuMgr* s_pInstance;
};
ASSERT_SIZE(BsMenuMgr, 0x20c);

#endif
