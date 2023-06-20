#ifndef SSYS_MA_LYT_FRAMECTRL_HPP
#define SSYS_MA_LYT_FRAMECTRL_HPP

#include "types.h"


namespace ssys::ma::lyt
{

	class FrameCtrl
	{

	public:

		
		virtual ~FrameCtrl();

		inline void* GetNwAnim() { return m_pNwAnim; }

		
	private:

		u8 m_Data[0x14];
		void* m_pNwAnim;
	};
	ASSERT_SIZE(FrameCtrl, 0x1c);
}

#endif
