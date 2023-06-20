#ifndef SSYS_MA_LYT_LAYOUTMGR_HPP
#define SSYS_MA_LYT_LAYOUTMGR_HPP

#include "ssys/ma/lyt/Layout.hpp"


namespace ssys::ma::lyt
{

	class LayoutMgr
	{

	public:

		static LayoutMgr* Get();

		void Register(Base2D* b2d, bool bottomScreen);
	};


}

#endif
