#pragma once

#include <nn/math/MTX34.hpp>
#include <nn/math/MTX44.hpp>
#include <nw/font/CharWriter.hpp>

namespace nw::font
{

	class RectDrawer
	{

	public:

		virtual ~RectDrawer();
		virtual void Finalize();
		virtual u32* DrawBegin(u32 options = 0);
		virtual u32* DrawBegin(u32* cmdbuf, u32 options = 0);
		virtual u32* DrawEnd(u32 options = 0);
		virtual u32* DrawEnd(u32* cmdbuf, u32 options = 0);

		u32* SetProjectionMtx(u32* cmdbuf, const nn::math::MTX44& proj);

		u32* SetViewMtx(u32* cmdbuf, const nn::math::MTX34& view)
		{
			m_ViewMtxComponentCount = 3;
			*reinterpret_cast<nn::math::MTX34*>(&m_ViewMtxCmdBuffer[3]) = view;
			return AddUniformMtx(cmdbuf);
		}

		u32* AddUniformMtx(u32* cmdbuf);

		void BuildTextCommand(CharWriter* writer);

	private:

		u8 m_Unk0[0x10];
		u8 m_Unk1[0x10];
		u8 m_ComponentCount1;
		u8 m_ViewMtxComponentCount;
		u8 m_ComponentCount3;
		u8 m_ComponentCount4;
		u32 m_ProjectionMtxCmdBuffer[24];
		u32 m_Unk3[108];
		u32 m_ViewMtxCmdBuffer[132];
		u32 m_Unk4[132];
		u32 m_Unk5[15];
	};
	ASSERT_SIZE(RectDrawer, 0x694);
}
