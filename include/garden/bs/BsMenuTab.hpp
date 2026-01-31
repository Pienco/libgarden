#pragma once

#include "Base.hpp"
#include "ButtonActionControlEx.hpp"
#include "../state/Mode.hpp"
#include "../script/RenderGarden.hpp"

#include "sead/EnumBitFlag.hpp"

class BsMenuTab : public Base, public state::Mode<BsMenuTab>
{
	friend class state::Mode<BsMenuTab>;

protected:

	enum TabID : u8
	{
		ITEM,
		DESIGN,
		REFERENCE,
		TPC,
		FRIEND_LIST,
		PLUS,
		CHAT,
		MANP,
		POST,
		CALL,
		BACK,
		DUMMY,
		COUNT = DUMMY,
	};

public:

	static constexpr size_t TAB_COUNT = TabID::COUNT;

	template<typename T>
	using TabArray = std::array<T, TAB_COUNT>;

	BsMenuTab();

	virtual ~BsMenuTab() override;
	virtual ProcessResult Initialize() override;
	virtual ProcessResult Finalize() override;
	virtual ProcessResult Calc() override;
	virtual ProcessResult Draw() override;

	static void SetMenuIn()
	{
		s_Flags &= ~Flags::MENU_IN_DONE;
		s_Flags |= Flags::MENU_IN;
	}
	static void SetMenuInDone() { s_Flags |= Flags::MENU_IN_DONE; }
	static void SetMenuOutDone() { s_Flags &= ~(Flags::MENU_IN | Flags::MENU_IN_DONE); }
	static bool IsRequireMenuOut() { return s_Flags & Flags::MENU_OUT; }
	static void SetMenuOut() { s_Flags &= ~Flags::MENU_OUT; }

	template<bool Out>
	static void SetMenuInOut()
	{
		if constexpr (Out) SetMenuOut();
		else SetMenuIn();
	}

	template<bool Out>
	static void SetMenuInOutDone()
	{
		if constexpr (Out) SetMenuOutDone();
		else SetMenuInDone();
	}

protected:

	using TabBits = sead::EnumBitFlag<TabID, u16>;

	enum class Mode : u8
	{
		NONE,
		TAB_SELECTION,
		WAIT,
		MENU_IN,
		TOP_TAB_OUT,
	};

	enum Flags : u32
	{
		MENU_IN = 1 << 3,
		MENU_IN_DONE = 1 << 4,
		MENU_OUT = 1 << 5,
		DO_NOT_UPDATE_BUTTONS = 1 << 11,
		INVENTORY_TAB_ONLY = 1 << 14,
	};

	static bool CheckInput();

	bool IsAnim(TabID tab) const { return m_BoundTabAnimsBits.IsSet(tab); }
	bool IsVisible(TabID tab) const { return m_VisibleTabsBits.IsSet(tab); }

	bool IsTabOpen() const { return m_CurrentTab >= 0; }

	bool IsInventoryTabOnly() const { return (s_Flags & Flags::INVENTORY_TAB_ONLY) != 0; }

	void UpdateIn();
	void BindIn();
	void BindOut();
	bool AnimateIn();
	bool AnimateOut();
	void UpdateUpperTabAppearance();
	void UpdateLowerTabAppearance();

	void CheckFriendOnline();

	void Trans_SwitchMenu();

	void State_TabSelection();
	void State_MenuOut();
	void State_ImageUp();
	void State_ExitIslandPressed();
	void State_Wait();
	void State_MenuIn();
	void State_TopTabOut();
	void State_TabChatExit();
	void State_WaitMenuEnd();

	static constexpr s8 NONE = -1;

	ArcReader m_ArcReader;
	Layout m_MenuTab;
	Animation m_In;
	Animation m_Out;
	Animation m_ChatOnly;
	Animation m_FriendOn;
	Animation m_PlusOn;
	ButtonActionControlEx m_ButtonControl1;
	ButtonActionControlEx m_ButtonControl2;
	TabArray<ButtonActionNodeEx> m_ActionNodes;
	script::RenderGarden m_Render;
	s32 m_State;
	bool m_Active;
	bool m_InSoundPlayed;
	u8 m_IsIn;
	bool m_Animating;
	u8 m_IsOut;
	bool m_NewFriendOnline;
	u8 m_TabSelection;
	u8 m_TopTabMode;
	bool m_AnimatingLower;
	bool m_AnimatingOutLower;
	u8 unk3;
	s8 m_CurrentTab;
	Mode m_Mode;
	TabArray<Group*> m_pGroups;
	TabArray<Pane*> m_pPanes;
	Pane* m_pChatScrn;
	Pane* m_pManp;
	Pane* m_pFriOn;
	Pane* m_pMark;
	Pane* m_pImTab01;
	Pane* m_pImTab0;
	Group* m_pGFriOn;
	Group* m_pGPlusOn;
	float m_ChatX;
	float m_ManpX;
	s32 unk4;
	s32 m_FriendOnTime;
	s32 m_PlusOnTime;
	s32 m_DialogMode;
	TabBits m_DisableBits;
	TabBits m_VisibleTabsBits;
	TabBits m_BoundTabAnimsBits;

	static u32 s_Flags;
	static bool s_WasBackPressed;
};
ASSERT_SIZE(state::Mode<BsMenuTab>, 0x24);
ASSERT_SIZE(BsMenuTab, 0x19b8);
