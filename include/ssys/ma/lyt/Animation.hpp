#ifndef SSYS_MA_LYT_ANIMATION_HPP
#define SSYS_MA_LYT_ANIMATION_HPP

#include "ssys/ma/lyt/FrameCtrl.hpp"
#include "ssys/ma/lyt/ResAccInterface.hpp"

namespace ssys::ma::lyt
{

	class Animation final : public FrameCtrl
	{
	
	public:

		Animation();

		virtual ~Animation() override;
		
		bool Initialize(const char* name, const ResAccInterface* resAcc);
		bool IsDone() const;
		void IncreaseFrame();
		inline bool IsBound() { return m_IsBound == 1; }
		inline bool IsUnbound() { return m_IsBound == 0; }
		


	private:

		u8 m_IsBound;
		u8 unk1;
		s16 unk2;
		s32 unk3;
		u8 unk4[4];
	};
	ASSERT_SIZE(Animation, 0x28);
}

#endif
