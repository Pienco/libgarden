#pragma once

#include "TransformNode.hpp"

namespace g3d
{
	class Model : public TransformNode
	{
	public:
		virtual ~Model() override;
		virtual void Finalize() override;

	private:
		u8 unknown;
	};
	ASSERT_SIZE(Model, 0xc);
}
