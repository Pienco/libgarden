#ifndef FONT_MGR_HPP
#define FONT_MGR_HPP

#include "nw/font/Font.hpp"
#include "sead/String.hpp"

namespace font
{

	enum class FontID
	{
		GARDEN_MSG_16,
		GARDEN_RUBY,
		GARDEN_NO,
		GARDEN_NO_F16,
		UNK
	};

	struct FontInfo
	{
		const char* name;
		const nw::font::Font* font;
	};

	class Mgr
	{

	public:

		static Mgr* Get() { return s_pInstance; }
		static FontInfo GetFontInfo(FontID font = FontID::GARDEN_MSG_16)
		{
			auto* const mgr = Get();
			return { mgr->GetFontName(font)->GetString(), mgr->GetFont(font) };
		}


		const sead::FixedSafeString<32>* GetFontName(FontID font) const;
		const nw::font::Font* GetFont(FontID font) const;


	private:

		static Mgr* s_pInstance;
	};

}

#endif
