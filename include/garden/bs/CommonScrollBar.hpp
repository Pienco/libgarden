#pragma once

#include "Layout.hpp"

enum class ScrollBarSize : u8
{
	LARGE,
	MEDIUM,
	SMALL,
};

struct ScrollBarDescription
{
	using Callback = void(*)(void*);

	ScrollBarSize size;
	float scrollSpace;
	s32 scrollSteps1;
	s32 scrollSteps2;
	s32 unk0;
	Callback callback1;
	Callback callback2;
};
ASSERT_SIZE(ScrollBarDescription, 0x1c);

class CommonScrollBar
{
public:
	CommonScrollBar(void* container);
	~CommonScrollBar();
	void Initialize(ScrollBarDescription&& desc);
	void Finalize();
	void SetParent(Pane* parent);
	void Process();

	s32 GetScroll() const
	{
		return m_Scroll;
	}

private:
	u8 m_Data[0x71c];
	s32 m_Scroll;
	u8 m_Data2[0x78];

};
ASSERT_SIZE(CommonScrollBar, 0x798);
