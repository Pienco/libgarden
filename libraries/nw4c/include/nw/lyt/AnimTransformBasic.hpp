#pragma once

#include <nw/lyt/AnimTransform.hpp>
#include <nw/lyt/AnimationLink.hpp>
#include <nw/lyt/ResourceAccessor.hpp>

namespace nw::lyt
{
	class AnimTransformBasic : public AnimTransform
	{
	public:
		virtual ~AnimTransformBasic() override;

		virtual void Animate(u32 index, class Pane* pane);
		virtual void Animate(u32 index, class Material* material);
		virtual void SetResource(const res::AnimationBlock* resource, ResourceAccessor* resAcc);
		virtual void SetResource(const res::AnimationBlock* resource, ResourceAccessor* resAcc, u16);
		virtual void Bind(class Pane*, bool, bool);

	private:
		void* m_pData;
		AnimationLink* m_pLinks;
		u16 m_LinkCount;
	};
	ASSERT_SIZE(AnimTransformBasic, 0x20);
}
