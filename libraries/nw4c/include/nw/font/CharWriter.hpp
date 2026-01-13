#pragma once

#include <nw/font/TextWriterResource.hpp>
#include <nw/font/Font.hpp>
#include <nw/ut/Color.hpp>
#include <nw/font/DispStringBuffer.hpp>

#include <nn/math/VEC2.hpp>
#include <nn/math/VEC3.hpp>

namespace nw::font
{

	class CharWriter
	{

	public:

		enum class TextGradient : u8
		{
			NONE,
			HORIZONTAL,
			VERTICAL,
		};

		CharWriter();

		void SetFont(const Font* font) { m_pFont = font; }
		void SetDispStringBuffer(DispStringBuffer* buf) { m_pDispBuffer = buf; }
 		void SetFontSize(float width, float height);

		void SetTextColors(ut::Color8 top, ut::Color8 bottom)
		{
			m_Gradient = top == bottom ? TextGradient::NONE : TextGradient::VERTICAL;
			m_TextColors[0] = top;
			m_TextColors[1] = bottom;
			UpdateVertexColors();
		}

		float GetCursorX() const { return m_Cursor[0]; }
		float GetCursorY() const { return m_Cursor[1]; }

		void StartPrint();
		u32* UseCommandBuffer(u32* cmdbuf, class RectDrawer* drawer);

		static constexpr u32 GetDispStringBufferSize(u32 charCount)
		{
			u32 cap = DispStringBuffer::CalcCommandBufferCapacity(charCount);
			return ((((((charCount + 7) >> 3) + 3) & 0xfffffffc) + charCount * 0x2c + 0x37) & 0xfffffff0) + cap * 4;
		}

		static DispStringBuffer* InitDispStringBuffer(void *mem, u32 charCount);

	private:

		void UpdateVertexColors();

		ut::Color8 m_Color0;
		ut::Color8 m_Color1;
		ut::Color8 m_VertexColors[4];
		ut::Color8 m_TextColors[2];
		TextGradient m_Gradient;
		nn::math::VEC2 m_Scale;
		nn::math::VEC3 m_Cursor;
		f32 m_FixedWidth;
		const Font* m_pFont;
		TextWriterResource* m_pResource;
		DispStringBuffer* m_pDispBuffer;
		bool m_UseFixedWidth;
		u8 m_Alpha;
	};
	ASSERT_SIZE(CharWriter, 0x4c);
}