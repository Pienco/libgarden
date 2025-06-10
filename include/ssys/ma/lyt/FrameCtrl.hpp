#ifndef SSYS_MA_LYT_FRAMECTRL_HPP
#define SSYS_MA_LYT_FRAMECTRL_HPP

#include "types.h"


namespace ssys::ma::lyt
{

	class FrameCtrl
	{

	public:

		virtual ~FrameCtrl();
		virtual void SetFrame(float frame) final // __attribute__((pcs("aapcs-vfp")))
		{
			m_PrevFrame = frame;
			m_Frame = frame;
			*(float*)(m_pNwAnim + 0x10) = frame;
		} 
		
		void SetFirstFrame() { SetFrame(0.0f); }
		void SetFrameR(float r) { SetFrame(m_FrameCount - r); }
		void SetLastFrame() { SetFrame(m_FrameCount - 1.0f); }

		void* GetNwAnim() { return m_pNwAnim; }
		float GetFrame() const { return m_Frame; }
		float GetFrameCount() const { return m_FrameCount; }

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
