#ifndef SCRIPT_RENDERGARDEN_HPP
#define SCRIPT_RENDERGARDEN_HPP

#include "script/RenderMain.hpp"
#include "script/RenderTrace.hpp"
#include "script/Word.hpp"
#include "nw/lyt/TextBox.hpp"

namespace script
{

	using TextBox = nw::lyt::TextBox;


	class RenderGarden
	{

	public:

		RenderGarden(size_t length);
		~RenderGarden();

		void SetTextBoxes(TextBox* textBox, TextBox* textBox2 = nullptr);
		void SetText(const IWord* text);
		void SetText(const char16* text = nullptr)
		{
			static constexpr char16* CHAR16_NULLPTR = nullptr;
			
			m_RenderMain.ClearBuf2();
			m_pCurTextBox = m_pTextBox;
			m_pCurTextBoxA = m_pTextBox2;
			m_RenderTrace.SetText(&text, &CHAR16_NULLPTR);
			m_RenderTrace.SetText2(&CHAR16_NULLPTR);
			m_pCurTextBox = nullptr;
			m_pCurTextBoxA = nullptr;
		}

		void CommitText();
		void Clear();

	private:

		RenderMain m_RenderMain;
		RenderTrace m_RenderTrace;
		s32 m_Unk0;
		s32 m_Unk1;
		TextBox* m_pCurTextBox;
		TextBox* m_pCurTextBoxA;
		s32 m_Unk2;
		TextBox* m_pTextBox;
		TextBox* m_pTextBox2;
		bool m_TextBoxesSet;
		INSERT_PAD(3);
	};
	ASSERT_SIZE(RenderGarden, 0xc4);

}

#endif
