#ifndef SSYS_MA_LYT_LAYOUTMGR_HPP
#define SSYS_MA_LYT_LAYOUTMGR_HPP

#include "ssys/ma/lyt/Layout.hpp"


namespace ssys::ma::lyt
{

	class LayoutMgr
	{

	public:

		inline static LayoutMgr* Get() { return s_pInstance; }

		void Register(Base2D* b2d, bool bottomScreen);

	private:

		static LayoutMgr* s_pInstance;
	};


}

#endif
