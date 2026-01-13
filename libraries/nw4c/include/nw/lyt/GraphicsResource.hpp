#pragma once

#include <nw/font/TextWriterResource.hpp>
#include <nn/math/MTX44.hpp>

namespace nw::lyt
{
	class GraphicsResource
	{

	public:

		auto& GetTextWriterResource() { return m_TextWriterResource; }

		void ResetGlState();
		void ResetGlProgramState();

		void SetProjectionMtx(const nn::math::MTX44 &mtx);

		static void FinalizeGraphics();

	private:
		u8 data[8];
		font::TextWriterResource m_TextWriterResource;
		u8 data2[0x1ec];
	};
	ASSERT_SIZE(GraphicsResource, 0x2e4);
}