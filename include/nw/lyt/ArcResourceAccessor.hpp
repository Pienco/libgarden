#ifndef NW_LYT_ARCRESOURCEACCESSOR_HPP
#define NW_LYT_ARCRESOURCEACCESSOR_HPP

#include "nw/lyt/ResourceAccessor.hpp"

#include "nw/font/Font.hpp"

namespace nw::lyt
{

	class ArcResourceAccessor : ResourceAccessor
	{

	public:

		void* RegistFont(const char* name, const font::Font* font);

		bool Attach(const void* data, const char* rootName);
	
	private:

		u8 m_Data[0x138];
	};
	ASSERT_SIZE(ArcResourceAccessor, 0x13c);
}

#endif
