#ifndef BS_BUTTONACTIONCONTROL_HPP
#define BS_BUTTONACTIONCONTROL_HPP

#include "bs/Layout.hpp"
#include "ssys/st/List.hpp"
#include "bs/ButtonActionNode.hpp"

class ButtonActionControl: ssys::st::List
{

public:

	enum Flag: u32
	{
		OK_DONE = 1,
		IS_SELECTING_OK = 2,
		DISABLED = 8,
		ENABLE_BUTTON_SHORTCUT = 0x40,
		FLAG_80 = 0x80,
		FLAG_100 = 0x100,
	};

	enum Flag2 : u8
	{
		ENABLE_CURSOR = 0x2,
		ENABLE_CURSOR_PERMANENT = 0x4,
		ENABLE_NODE_SHORTCUT = 0x8,
		CAN_RELEASE = 0x10,
		WAIT_FOR_SELECT_RELEASE = 0x20,
		NODE_OK_IMMEDIATE = 0x40,
	};

	using Predicate = bool(*)();

	struct Description
	{
		ssys::ma::lyt::ResAccInterface* resAcc;
		Layout* layout;
		Bounding* bounding = nullptr;
		const char* touch = nullptr;
		const char* select = nullptr;
		const char* touchOk = nullptr;
		const char* selectOk = nullptr;
		s32 cursorTimer = 0;
		Predicate checkInput = nullptr;
	};
	ASSERT_SIZE(Description, 0x24);

	ButtonActionControl();

	virtual ~ButtonActionControl() override;
	virtual void UpdateState();
	virtual void Reset();
	virtual void Process();
	virtual void ProcessOk();
	virtual void CheckInputForNode();
	virtual void CheckInputForNodeOk();
	virtual void CheckInputForNodeTouch();
	virtual void CheckRelease();
	virtual void UpdateCurrentTouched();
	virtual void SelectCurrent();
	virtual void FUN_002f6ee4();
	virtual void OnBegin();
	virtual void FUN_002f7300();

	void SetFlags(u32 flags, bool set = true)
	{
		if (set) m_Flags |= flags;
		else m_Flags &= ~flags;
	}

	void SetFlags2(u16 flags, bool set = true)
	{
		if (set) m_Flags2 |= flags;
		else m_Flags2 &= ~flags;
	}

	void Initialize(const Description& desc, const char* animNamePrefix = nullptr);
	void AddNode(ButtonActionNode* node, bool updateAnimations = true);
	void Update();
	bool IsSelectOkDone() const;
	bool IsSelectOkOngoing() const { return m_pFunc == &ButtonActionControl::State_Selecting; }
	s32 GetSelectedIndex() const;
	s32 GetPressedIndex() const;
	ButtonActionNode* GetCurrent() { return m_pCurrent; }
	bool HasCurrent() const { return m_pCurrent != nullptr; }
	void SetCursor(bool enable);
	void UnselectCurrent();
	void UnselectActive();
	void ResetAndUnselectCurrent()
	{
		UnselectCurrent();
		Reset();
	}

private:

	void State_Selecting();

	using Func = void(ButtonActionControl::*)();


	Layout* m_pLayout;
	Animation m_Touch;
	Animation m_Select;
	Animation m_TouchOk;
	Animation m_SelectOk;
	Bounding* m_pBounding;
	ButtonActionNode* m_pCurrent;
	Func m_pFunc;
	Predicate m_pCheckInput;
	u32 m_CursorInput;
	u32 m_ReleaseInput;
	s32 m_CursorTimer;
	u16 m_Flags2;
	u8 m_CurrentIndex;
	u32 m_Flags;
	s32 m_Counter;
	s32 m_MaxCounter;
	u32 unk;
};
ASSERT_SIZE(ButtonActionControl, 0xe4);

#endif
