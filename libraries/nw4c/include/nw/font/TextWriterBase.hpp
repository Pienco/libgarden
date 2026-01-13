#pragma once

#include <nw/font/CharWriter.hpp>
#include <nw/font/TagProcessorBase.hpp>

namespace nw::font
{

	template<typename T>
	class TextWriterBase : public CharWriter
	{
	
	public:

		enum Alignment : u32
		{
			LEFT = 0,
			CENTER = 1,
			RIGHT = 2,
			TOP = 0,
			BOTTOM = 2,
		};

		TextWriterBase();

		float CalcStringWidth(const T* str, s32 len) const;
		float Print(const T* str, s32 len) const;

		void SetCharSpace(float value) { m_CharSpace = value; }
		void SetLineSpace(float value) { m_LineSpace = value; }
		void SetWidthLimit(float value) { m_WidthLimit = value; }
		void SetTagProcessor(TagProcessorBase<char16>* value) { m_pTagProcessor = value; }

		void SetTextAlignment(Alignment originX, Alignment originY, Alignment text)
		{
			m_TextAlignment = text;
			m_OriginX = originX;
			m_OriginY = originY;
		}

	private:

		float m_WidthLimit;
		float m_CharSpace;
		float m_LineSpace;
		s32 m_TabWidth;
		Alignment m_TextAlignment : 4;
		Alignment m_OriginX : 4;
		Alignment m_OriginY : 4;
		TagProcessorBase<char16>* m_pTagProcessor;
	};

	using TextWriter = TextWriterBase<char>;
	using WideTextWriter = TextWriterBase<char16_t>;

	ASSERT_SIZE(TextWriter, 0x64);
	ASSERT_SIZE(WideTextWriter, 0x64);
}