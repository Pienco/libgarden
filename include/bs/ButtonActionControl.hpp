#ifndef BS_BUTTONACTIONCONTROL_HPP
#define BS_BUTTONACTIONCONTROL_HPP

#include "bs/Layout.hpp"
#include "ssys/st/List.hpp"
#include "bs/ButtonActionNode.hpp"

class ButtonActionControl: ssys::st::List
{

public:

	enum Flag : u32
	{
		IS_SELECTING_CURRENT = 1,
		IS_SELECTING = 2,
		DISABLED = 8,
		ENABLE_BUTTON_SHORTCUT = 0x40,
		FLAG_80 = 0x80,
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
	virtual void BeginProcess();
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

	inline void SetFlags(u32 flags, bool set = true) 
	{
		if (set) m_Flags |= flags;
		else m_Flags &= ~flags;
	}

	inline void SetFlags2(u16 flags, bool set = true)
	{
		if (set) m_Flags2 |= flags;
		else m_Flags2 &= ~flags;
	}

	void Initialize(const Description& desc, const char* animNamePrefix = nullptr);
	void AddNode(ButtonActionNode* node, bool updateAnimations = true);
	void Update();
	bool IsSelecting() const;
	inline bool IsStateSelecting() const { return m_pFunc == &ButtonActionControl::State_Selecting; }
	s32 GetPressedButtonIndex() const;
	s32 GetCurrentPressedIndex() const;
	inline ButtonActionNode* GetCurrent() { return m_pCurrent; }
	inline bool HasCurrent() const { return m_pCurrent != nullptr; }
	void SetCursor(bool enable);
	void Unselect();
	void UnselectActive();

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
