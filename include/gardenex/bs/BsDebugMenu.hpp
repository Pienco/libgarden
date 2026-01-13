#pragma once

#include <gardenex/state/State.hpp>
#include <garden/bs/Base.hpp>
#include <garden/bs/Layout.hpp>
#include <garden/script/RenderRuby.hpp>

namespace gardenex
{

class BsDebugMenu final : public Base
{
public:

	using Self = BsDebugMenu;

	void AddText(const char16* text, size_t length)
	{
		AddTextImpl<false>(text, length);
	}
	
	template<size_t N>
	void AddText(const char16(&text)[N])
	{
		AddText(text, N - 1);
	}

	void AddLine(const char16* text, size_t length)
	{
		AddTextImpl<true>(text, length);
	}

	template<size_t N>
	void AddLine(const char16(&text)[N])
	{
		AddLine(text, N - 1);
	}

	template<bool Line>
	void AddTextImpl(const char16* text, size_t length)
	{
		size_t newOffset = m_TextOffset + length;
		if constexpr (Line) newOffset++;
		if (newOffset < TEXT_BUFFER_LENGTH)
		{
			std::char_traits<char16>::copy(m_Text.data() + m_TextOffset, text, length);
			m_TextOffset = newOffset;
			if constexpr (Line) m_Text[m_TextOffset - 1] = u'\n';
			m_Text[m_TextOffset] = u'\0';
			m_State = &Self::State_TextAdded;
			UpdateText();
		}
	}

protected:

	virtual ProcessResult Initialize() override
	{
		if (!m_ArcReader.ReadArc("Layout/debug/debug_window.arc"))
			return ProcessResult::RETRY;
		m_Layout.SetArcResAccReader(&m_ArcReader);
		m_ArcReader.RegisterFont();
		m_Layout.Initialize("debug_window.bclyt", &m_ArcReader, 0xff, 0x1000);

		m_TextRender.SetTextBoxes(m_Layout.FindTextBox("debug_text"));
		AddLine(u"Hello world");
		return ProcessResult::SUCCESS;
	}

	virtual ProcessResult Finalize() override
	{
		m_Layout.UnbindAllAnimation();
		m_TextRender.Clear();
		m_ArcReader.Clear();
		return ProcessResult::SUCCESS;
	}

	virtual ProcessResult Calc() override
	{
		m_State(this);
		return ProcessResult::SUCCESS;
	}

	virtual ProcessResult Draw() override
	{
		m_Layout.RegisterForDrawing(false);
		return ProcessResult::SUCCESS;
	}

private:

	static constexpr size_t TEXT_BUFFER_LENGTH = 512;
	static constexpr u32 VISIBILITY_TIME = 230;

	void State_Wait() { }

	void State_Visible()
	{
		if (--m_Timer != 0) return;
		m_Layout.GetRootPane()->SetVisible(false);
		m_Layout.Animate();
		m_Text[0] = 0;
		m_TextOffset = 0;
		m_State = &Self::State_Wait;
	}

	void State_TextAdded()
	{
		m_Timer = VISIBILITY_TIME;
		m_Layout.GetRootPane()->SetVisible(true);
		m_Layout.Animate();
		m_State = &Self::State_Visible;
	}

	void UpdateText()
	{
		m_TextRender.SetText(m_Text.data());
		m_TextRender.CommitText();
	}

	state::State<Self> m_State { &Self::State_Wait };
	u32 m_Timer;
	size_t m_TextOffset; 
	Layout m_Layout;
	ArcReader m_ArcReader;
	std::array<char16, TEXT_BUFFER_LENGTH> m_Text;
	script::RenderRuby m_TextRender { TEXT_BUFFER_LENGTH, 0 };
};

}
