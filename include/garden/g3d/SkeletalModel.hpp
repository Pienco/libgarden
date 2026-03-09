#pragma once

#include "Model.hpp"

namespace g3d
{
	class SkeletalModel : public Model
	{
	public:
		virtual ~SkeletalModel() override;
		virtual void Update() override;

	private:
	};
	ASSERT_SIZE(SkeletalModel, 0xc);
}
