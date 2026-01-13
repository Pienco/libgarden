#ifndef BS_BUTTONACTIONNODE_HPP
#define BS_BUTTONACTIONNODE_HPP

#include "Layout.hpp"
#include "../ssys/st/ListNode.hpp"
#include "../SoundMgr.hpp"

class ButtonActionNode : ssys::st::ListNode
{

public:

	ButtonActionNode();
	virtual ~ButtonActionNode();
	virtual bool IsActivated() const { return m_IsActive; }
	virtual void ResetSelect();
	virtual void FUN_002b72e0();
	virtual bool IsTouch() const;
	virtual bool IsCursorHover() const;
	virtual void TouchSelect(bool touch, bool sound);
	virtual void Select(bool select, bool sound);
	virtual void BeginSelectOk();
	virtual void EndSelectOk();
	virtual bool IsOkOngoing() const;
	virtual void DoOk();

	struct Info
	{
		Pane* pane;
		Group* group;
		math::Vector2 pos;
		s32 input;
		size_t index;
		s32 unk;
	};

	void Initialize(const Info& info);
	void InitializeAndEnableSound(const Info& info, SeID select, SeID ok)
	{
		EnableAllSound();
		SetSe(select, ok);
		Initialize(info);
	}

	void SetSoundEnabled(bool set) { m_SoundEnabled = set; }
	void SetOkSoundEnabled(bool set) { m_OkSoundEnabled = set; }
	void EnableAllSound() 
	{
		SetSoundEnabled(true);
		SetOkSoundEnabled(true);
	}
	void SetSe(SeID id) { m_Se = id; }
	void SetSeOk(SeID id) { m_SeOk = id; }
	void SetSe(SeID select, SeID ok)
	{
		m_Se = select;
		m_SeOk = ok;
	}
	void Deactivate() { m_IsActive = false; }
	void Activate() { m_IsActive = true; }
	void Select(bool set = true);
	void Unselect() { Select(false); }
	auto GetIndex() const { return m_Index; }

protected:

	virtual void Animate(Animation& anim, bool set);
	virtual void PlayOkSound();
	virtual void PlaySound();


private:

	Pane* m_pPane;
	Group* m_pGroup;
	math::Vector2 m_Position;
	Layout* m_pLayout;
	Animation m_Touch;
	Animation m_Select;
	Animation m_TouchOk;
	Animation m_SelectOk;
	s32 unk;
	u32 m_Input;
	s32 m_Index;
	SeID m_SeOk;
	SeID m_Se;
	u16 unk2;
	u8 unk3;
	bool m_IsPressed;
	u8 unk4;
	bool m_IsActive;
	bool m_OkSoundEnabled;
	bool m_SoundEnabled;
	bool m_SoundMode;
	bool m_IsAvailable;
};
ASSERT_SIZE(ButtonActionNode, 0xe0);

#endif
