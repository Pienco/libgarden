#ifndef SSYS_MA_LYT_BASE2D_HPP
#define SSYS_MA_LYT_BASE2D_HPP

#include "ssys/st/ListNode.hpp"

namespace ssys::ma::lyt
{

	class Base2D : st::ListNode
	{

	public:

		virtual void DrawBegin();
		virtual void Animate();
		virtual void BuildImpl();
		virtual void Draw();
		virtual void Update();

		inline void SetLayer(u8 layer) { m_Layer = layer; }

	private:

		u8 m_Layer;
		INSERT_PAD(3);
	};
	ASSERT_SIZE(Base2D, 0x10);
}
#endif
