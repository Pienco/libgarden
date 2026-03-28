#pragma once

#include <nn/types.h>

namespace g3d
{
	class TransformNode
	{
	public:
		virtual ~TransformNode();
		virtual void Update();
		virtual void Finalize();

	private:
		void* m_pNode;
	};
	ASSERT_SIZE(TransformNode, 0x8);
}
