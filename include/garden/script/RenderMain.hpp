#pragma once

#include "RenderBase.hpp"

namespace script
{

	class RenderMain : public RenderBase
	{
	public:

		RenderMain(size_t textBufCapacity = 0, size_t storeBufCapacity = 0, size_t tagBufCount = 0);
		virtual ~RenderMain() override;

	private:
		s32 m_Offset;
		void * m_pUnk0;
		size_t m_Size;
		s32 m_Unk1;
		nn::math::VEC2 m_Unk2;
	};
	ASSERT_SIZE(RenderMain, 0x44);
}
