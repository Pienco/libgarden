#ifndef SCRIPT_RENDERMAIN_HPP
#define SCRIPT_RENDERMAIN_HPP

#include "script/RenderBase.hpp"

namespace script
{

	class RenderMain : public RenderBase
	{

	public:

		virtual ~RenderMain() override;

	private:

		s32 m_Offset;
		void * m_pUnk0;
		size_t m_Size;
		s32 m_Unk1;
		math::Vector2 m_Unk2;
	};
	ASSERT_SIZE(RenderMain, 0x44);
}

#endif
