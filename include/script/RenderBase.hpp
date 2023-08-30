#ifndef SCRIPT_RENDERBASE_HPP
#define SCRIPT_RENDERBASE_HPP


#include "nw/font/TagProcessorBase.hpp"
#include "nw/ut/types.hpp"
#include "math/Vector.hpp"

namespace script
{

	using Color8 = nw::ut::Color8;

	class RenderBase : public nw::font::TagProcessorBase<char16>
	{

	public:

	public:

		inline void ClearBuf2()
		{
			if (m_pBuf2 != nullptr)
				*m_pBuf2 = 0;
		}

	private:

		Color8 m_TextColors[2];
		Vector2 m_FontSize;
		char16* m_pText;
		size_t m_Len;
		s32 m_Count;
		void* m_pBuf;
		u8* m_pBuf2;
		char16* m_pEnd;
	};
	ASSERT_SIZE(RenderBase, 0x2c);
}

#endif
