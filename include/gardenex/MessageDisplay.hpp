#pragma once

#include "layout.hpp"

#include <string_view>

namespace gardenex
{
	class MessageDisplay
	{
	public:
		MessageDisplay() = default;
		MessageDisplay(nw::ut::Color8 topColor, nw::ut::Color8 bottomColor)
			: m_TextColors{topColor, bottomColor} { }

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

			for (size_t i = expired; i < m_Lines.size(); i++)
				m_Lines[i].end -= offset;
			std::copy(m_Lines.begin() + expired, m_Lines.end(), m_Lines.begin());
			m_LineCount -= expired;
			m_Dirty = true;
		}

		void Draw()
		{
			if (m_LineCount == 0) return;

			nw::font::WideTextWriter writer;
			writer.SetDispStringBuffer(m_Display.GetBuffer());
			writer.SetTextColors(m_TextColors[0], m_TextColors[1]);

			if (m_Dirty)
			{
				PrintTextScope printer {writer, 13.0f, 17.33333f};
				using enum nw::font::WideTextWriter::Alignment;
				writer.SetTextAlignment(RIGHT, BOTTOM, RIGHT);
				writer.SetLineSpace(-4.0f);
				writer.Print(m_Text.data(), static_cast<s32>(m_Lines[m_LineCount - 1].end));
				m_Dirty = false;
			}

			DrawText(textPosition, writer);
		}

		void Show(std::u16string_view str)
		{
			if (m_LineCount == maxLineCount) m_LineCount--;
			size_t offset = m_LineCount == 0 ? 0 : m_Lines[m_LineCount - 1].end + 1;
			size_t end = offset + str.size();
			if (end >= textBufSize) return;
			if (offset > 0) m_Text[offset - 1] = u'\n';

			Traits::copy(m_Text.data() + offset, str.data(), str.size());
			m_Lines[m_LineCount] = {.end = static_cast<u16>(end), .timer = displayTime};
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

		static constexpr size_t textBufSize = 160;
		static constexpr size_t maxLineCount = 9;
		static constexpr nn::math::VEC2 textPosition {392.0f, 228.0f};
		static constexpr u16 displayTime = 180;

		std::array<nw::ut::Color8, 2> m_TextColors {nw::ut::Color8::White(), {0x90, 0x90, 0x90, 0xff}};
		std::array<Line, maxLineCount> m_Lines {};
		size_t m_LineCount {};
		std::array<char16, textBufSize> m_Text;
		bool m_Dirty = true;
		TextDisplayMem<textBufSize> m_Display;
	};
}
