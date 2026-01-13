#pragma once

#include "MsgEngine.hpp"

namespace script
{
	class RenderTrace final : MsgEngine
	{
	public:
		void SetText(const char16* const* text, const char16* const* textA);
		void SetText2(const char16* const* text);

	private:
		s32 m_MessageCount;
	};
	ASSERT_SIZE(RenderTrace, 0x60);
}
