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

	class Mgr
	{

	public:

		static inline Mgr* Get() { return s_pInstance; }


		const sead::FixedSafeString<32>* GetFontName(FontID font) const;
		const nw::font::Font* GetFont(FontID font) const;

	private:

		static Mgr* s_pInstance;
	};

}

#endif
