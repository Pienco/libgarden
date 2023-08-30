#ifndef BS_BUTTONACTIONCONTROLEX_HPP
#define BS_BUTTONACTIONCONTROLEX_HPP

#include "bs/ButtonActionControl.hpp"
#include "bs/ButtonActionNodeEx.hpp"

class ButtonActionControlEx final : public ButtonActionControl
{

public:

	struct Description
	{
		ssys::ma::lyt::ResAccInterface* resAcc;
		Layout* layout;
		Bounding* bounding = nullptr;
		const char* touch = nullptr;
		const char* select = nullptr;
		const char* touchOk = nullptr;
		const char* selectOk = nullptr;
		const char* touchBack = nullptr;
		const char* selectBack = nullptr;
		const char* touchOkBack = nullptr;
		const char* selectOkBack = nullptr;
		s32 cursorTimer = 0;
		ButtonActionControl::Predicate checkInput = nullptr;
	};
	ASSERT_SIZE(Description, 0x34);

	virtual ~ButtonActionControlEx() override;

	bool Initialize(const Description& desc);
	void AddNode(ButtonActionNodeEx* node, bool updateAnimations = true);

private:

	Animation m_TouchBack;
	Animation m_SelectBack;
	Animation m_TouchOkBack;
	Animation m_SelectOkBack;
};
ASSERT_SIZE(ButtonActionControlEx, 0x184);

#endif
