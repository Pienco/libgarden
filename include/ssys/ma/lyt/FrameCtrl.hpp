#ifndef SSYS_MA_LYT_FRAMECTRL_HPP
#define SSYS_MA_LYT_FRAMECTRL_HPP

#include "types.h"


namespace ssys::ma::lyt
{

	class FrameCtrl
	{

	public:

		
		virtual ~FrameCtrl();
		virtual inline void SetFrame(float frame) final // __attribute__((pcs("aapcs-vfp")))
		{
			m_PrevFrame = frame;
			m_Frame = frame;
			*(float*)(m_pNwAnim + 0x10) = frame;
		} 
		
		inline void SetFirstFrame() { SetFrame(0.0f); }
		inline void SetFrameR(float r) { SetFrame(m_FrameCount - r); }
		inline void SetLastFrame() { SetFrame(m_FrameCount - 1.0f); }

		inline void* GetNwAnim() { return m_pNwAnim; }
		inline float GetFrame() const { return m_Frame; }
		inline float GetFrameCount() const { return m_FrameCount; }

		
	private:

		float m_FrameCount;
		float m_Frame;
		float m_PrevFrame;
		float m_FrameIncrease;
		u8 m_Loop;
		u8* m_pNwAnim;
	};
	ASSERT_SIZE(FrameCtrl, 0x1c);
}

#endif
