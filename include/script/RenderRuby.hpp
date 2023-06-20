#ifndef SCRIPT_RENDERRUBY_HPP
#define SCRIPT_RENDERRUBY_HPP

#include "script/RenderMain.hpp"
#include "script/RenderTrace.hpp"
#include "script/Word.hpp"

#include "nw/lyt/TextBox.hpp"


namespace script
{
	using TextBox = nw::lyt::TextBox;


	class RenderRuby final : RenderMain
	{

	public:

		RenderRuby(size_t length = 0x80, size_t length2 = 0x40);
		virtual ~RenderRuby();

		void SetTextBoxes(const TextBox* text, const TextBox* textA = nullptr, const TextBox* text2 = nullptr, const TextBox* text2A = nullptr);

		// void SetText(const WordPtr* text);

		inline void SetText(const char16* text)
		{
			static constexpr char16* CHAR16_NULLPTR = nullptr;

			ClearBuf2();
			m_Render.ClearBuf2();
			m_pCurTextBox = m_pTextBox;
			m_pCurTextBoxA = m_pTextBoxA;
			m_RenderTrace.SetText(&text, &CHAR16_NULLPTR);
			m_RenderTrace.SetText2(&CHAR16_NULLPTR);
			m_pCurTextBox = nullptr;
			m_pCurTextBoxA = nullptr;
		}

		void CommitText();
		void Clear();

	private:

		RenderBase m_Render;
		s32 m_Unk0;
		s32 m_Unk1;
		RenderTrace m_RenderTrace;
		s32 m_Unk2;
		s32 m_Unk3;
		TextBox* m_pCurTextBox;
		TextBox* m_pCurTextBoxA;
		s32 m_Unk4;
		TextBox* m_pTextBox;
		TextBox* m_pTextBoxA;
		TextBox* m_pTextBox2;
		TextBox* m_pTextBox2A;
		bool m_TextBoxSet;
	};
	ASSERT_SIZE(RenderRuby, 0x100);
}

#endif
