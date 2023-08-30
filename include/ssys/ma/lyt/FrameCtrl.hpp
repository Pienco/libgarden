#ifndef SSYS_MA_LYT_FRAMECTRL_HPP
#define SSYS_MA_LYT_FRAMECTRL_HPP

#include "types.h"


namespace ssys::ma::lyt
{

	class FrameCtrl
	{

	public:

		
		virtual ~FrameCtrl();
		virtual void SetFrame(float frame) __attribute__((pcs("aapcs-vfp")));
		
		inline void SetFirstFrame() { SetFrame(0.0f); }
		inline void SetFrameR(float r) { SetFrame(m_FrameCount - r); }
		void SetLastFrame();

		inline void* GetNwAnim() { return m_pNwAnim; }
		inline float GetFrame() const { return m_Frame; }
		inline float GetFrameCount() const { return m_FrameCount; }

		
	private:

		float m_FrameCount;
		float m_Frame;
		u8 m_Data2[0xc];
		void* m_pNwAnim;
	};
	ASSERT_SIZE(FrameCtrl, 0x1c);
}

#endif
