#pragma once

#include <nw/lyt/common.hpp>
#include <nw/lyt/Pane.hpp>
#include <nw/lyt/Material.hpp>
#include <nw/font/Font.hpp>
#include <nw/font/TagProcessorBase.hpp>
#include <nw/font/DispStringBuffer.hpp>
#include <nw/ut/Color.hpp>

#include <libc.h>

#include <array>

namespace nw::lyt
{
	class TextBox final : public Pane
	{
	public:
		enum TextAlignment : u8
		{
			ORIGIN,
			LEFT,
			CENTER,
			RIGHT,
		};

		TextBox(math::Vector2 size, const font::Font* font, u16 maxCharCount, const char16* text, u16 length, Material* material) :
			Pane {size},
			m_pFont {font},
			m_pMaterial {material}
		{
			CreateTextBuffer(maxCharCount);
			SetText(text, 0, length);
		}

		virtual ~TextBox() override;

		virtual u32* GenCmd(u32* cmdbuf, DrawInfo& info, Drawer& drawer) override;

		virtual void CreateTextBuffer(u16 len, u32 options = 0);
		virtual void DestroyTextBuffer();
		virtual u16 SetText(const char16* text, u16 index = 0);
		virtual u16 SetText(const char16* text, u16 index, u16 length);

		void SetColors(ut::Color8 top, ut::Color8 bottom) { m_Colors = {top, bottom}; }
		void SetFontSize(const Vector2& value) { UpdateDirty(m_FontSize, value); }
		void SetLineSpace(float value) { UpdateDirty(m_LineSpace, value); }
		void SetCharSpace(float value) { UpdateDirty(m_CharSpace, value); }

		void SetTagProcessor(font::TagProcessorBase<char16>* value)
		{
			UpdateDirty(m_pTagProcessor, value);
		}

		void SetTextOrigin(OriginX x, OriginY y)
		{
			UpdateDirty(m_TextOrigin, EncodeOrigin(x, y));
		}

		void SetTextAlignment(TextAlignment value)
		{
			UpdateDirty(m_TextAlignment, value);
		}

		void SetDirty() { m_Dirty = true; }

		char16* GetText() { return m_pText; }
		const char16* GetText() const { return m_pText; }

		font::DispStringBuffer* GetDispStringBuffer() { return m_pDispStringBuffer; }

	private:
		bool UpdateDirty(auto& target, const auto& newValue)
		{
			if (target != newValue)
			{
				target = newValue;
				m_Dirty = true;
				return true;
			}
			return false;
		}

		char16* m_pText {};
		std::array<ut::Color8, 2> m_Colors {ut::Color8::White(), ut::Color8::White()};
		const font::Font* m_pFont;
		Vector2 m_FontSize {1.0f, 1.0f};
		float m_LineSpace {};
		float m_CharSpace {};
		font::TagProcessorBase<char16>* m_pTagProcessor {};
		u16 m_TextBufferSize; // in bytes
		u16 m_CharCount;
		u8 m_TextOrigin {GetOrigin()};
		TextAlignment m_TextAlignment {TextAlignment::ORIGIN};
		bool m_Dirty : 1 {true};
		Material* m_pMaterial;
		font::DispStringBuffer* m_pDispStringBuffer;
	};
	ASSERT_SIZE(TextBox, 0x108);
}
