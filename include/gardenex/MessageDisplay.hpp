#pragma once

#include "layout.hpp"

#include <nw/font/TextWriterBase.hpp>
#include <garden/ssys/ma/lyt/LayoutMgr.hpp>
#include <nn/gx/gx.h>

#include <string_view>

namespace gardenex
{
	class MessageDisplay
	{

	public:

		MessageDisplay()
		{
			nw::font::CharWriter::InitDispStringBuffer(m_DisplayMem, textBufLen);
		}

		void Update()
		{
			size_t expired = 0;
			for (size_t i = 0; i < m_LineCount; i++)
			{
				if (m_Lines[i].timer > 0) m_Lines[i].timer--;
				if (m_Lines[i].timer == 0) expired++;
			}
			if (expired == 0) return;
		
			u16 offset = m_Lines[expired - 1].end;
			u16 newLen = m_Lines[m_LineCount - 1].end - offset;
			Traits::move(m_Text.data(), m_Text.data() + offset, newLen);
			m_Text[newLen] = u'\0';
			for (size_t i = expired; i < m_Lines.size(); i++)
				m_Lines[i].end -= offset;
			std::copy(m_Lines.begin() + expired, m_Lines.end(), m_Lines.begin());
			m_LineCount -= expired;
			m_Dirty = true;
		}

		void Draw()
		{
			static constexpr nn::math::MTX34 mtx
			{
				1.0f, 0.0f, 0.0f, 380.0f,
				0.0f, 1.0f, 0.0f, 218.0f,
				0.0f, 0.0f, 1.0f, 0.0f
			};

			if (m_LineCount == 0) return;

			auto& drawer = ssys::ma::lyt::LayoutMgr::Get()->GetDrawer();
			nw::font::WideTextWriter writer;
			writer.SetDispStringBuffer(GetDispBuffer());
			writer.SetTextColors(nw::ut::Color8::White(), {0x77, 0x77, 0x77, 0xff});

			if (m_Dirty)
			{
				writer.SetFont(font::Mgr::Get()->GetFont(font::FontID::GARDEN_MSG_16));
				writer.SetFontSize(12.0f, 15.0f);
				writer.SetTagProcessor(&GetDummyTagProcessor());
				using enum nw::font::WideTextWriter::Alignment;
				writer.SetTextAlignment(RIGHT, BOTTOM, RIGHT);
				writer.StartPrint();
				writer.Print(m_Text.data(), static_cast<s32>(m_Lines[m_LineCount - 1].end));
				drawer.BuildTextCommand(&writer);
				m_Dirty = false;
			}

			u32* cmdbuf = drawer.DrawBegin();
			cmdbuf = drawer.SetProjectionMtx(cmdbuf, gardenex::GetProjectionMatrix(false, true));
			cmdbuf = drawer.SetViewMtx(cmdbuf, mtx);
			cmdbuf = writer.UseCommandBuffer(cmdbuf, &drawer);
			__cb_current_command_buffer = drawer.DrawEnd(cmdbuf);
		}

		void Show(std::u16string_view str)
		{
			if (m_LineCount == maxLineCount) m_LineCount--;
			size_t offset = m_LineCount == 0 ? 0 : m_Lines[m_LineCount - 1].end;
			size_t end = offset + str.size() + 1;
			if (end >= textBufLen) return;

			Traits::copy(m_Text.data() + offset, str.data(), str.size());
			*(m_Text.data() + end - 1) = u'\n';
			*(m_Text.data() + end) = u'\0';
			m_Lines[m_LineCount] = {.end = static_cast<u16>(end), .timer = 240};
			m_LineCount++;
			m_Dirty = true;
		}

	private:
		using Traits = std::char_traits<char16>;

		struct Line
		{
			u16 end {};
			u16 timer {};
		};

		nw::font::DispStringBuffer* GetDispBuffer()
		{
			return reinterpret_cast<nw::font::DispStringBuffer*>(&m_DisplayMem[0]);
		}

		static constexpr size_t textBufSize = 160;
		static constexpr size_t textBufLen = textBufSize - 1;
		static constexpr size_t maxLineCount = 9;

		std::array<Line, maxLineCount> m_Lines {};
		size_t m_LineCount {};
		std::array<char16, textBufSize> m_Text;
		bool m_Dirty = true;
		alignas(u32) u8 m_DisplayMem[nw::font::CharWriter::GetDispStringBufferSize(textBufLen)];
	};
}
