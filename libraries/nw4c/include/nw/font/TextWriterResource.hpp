#pragma once

#include <nn/math/MTX34.hpp>
#include <GLES2/gl2.h>

namespace nw::font
{

	class TextWriterResource
	{
	
	public:

		void UseProgram()
		{
			glUseProgram(m_ProgramId);
		}

		void SetViewMtx(const nn::math::MTX34& mtx);

		static void FinalizeGX();

	private:
		u32 m_ProgramId;
		u8 data[0xec];
	};
	ASSERT_SIZE(TextWriterResource, 0xf0);
}