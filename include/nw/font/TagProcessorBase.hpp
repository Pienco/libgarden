#ifndef NW_FONT_TAGPROCESSORBASE_HPP
#define NW_FONT_TAGPROCESSORBASE_HPP

#include "types.h"

namespace nw::font
{

	template<typename T>
	class TagProcessorBase
	{
	
	public:

		virtual ~TagProcessorBase();

	private:


	};
	ASSERT_SIZE(TagProcessorBase<char16>, 4);
	ASSERT_SIZE(TagProcessorBase<char>, 4);
}

#endif
