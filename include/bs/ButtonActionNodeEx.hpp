#ifndef BS_BUTTONACTIONNODEEX_HPP
#define BS_BUTTONACTIONNODEEX_HPP

#include "bs/ButtonActionNode.hpp"

class ButtonActionNodeEx final : public ButtonActionNode
{

public:

	ButtonActionNodeEx();
	virtual ~ButtonActionNodeEx() override;
	virtual void ResetSelect() override;
	virtual void TouchSelect(bool touch, bool sound) override;
	virtual void Select(bool select, bool sound) override;
	virtual void BeginSelectOk() override;
	virtual void EndSelectOk() override;
	virtual bool IsOkOngoing() const override;
	virtual void DoOk() override;

	void SetIsSelectBack(bool set) { m_IsBack = set; }
	void SetIsOkBack(bool set) { m_IsBack = set; }

	void SetIsBack(bool set) { SetIsSelectBack(set); SetIsOkBack(set); }

private:

	Animation m_TouchBack;
	Animation m_SelectBack;
	Animation m_TouchOkBack;
	Animation m_SelectOkBack;
	u8 m_IsBack;
	u8 m_IsOkBack;
	u8 unk2;
	u8 unk3;
};
ASSERT_SIZE(ButtonActionNodeEx, 0x184);

#endif
