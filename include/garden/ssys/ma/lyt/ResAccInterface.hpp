#pragma once

#include <nn/types.h>

namespace ssys::ma::lyt
{
	class ResAccInterface
	{
	public:
		virtual ~ResAccInterface();

	protected:
		// void SetData(const void* data)
		// {
		// 	ASSERT_OFFSET(ResAccInterface, m_pData, 8);

		// 	m_pData = data;
		// }

	private:
		void* m_pResourceAccessor;
		const void* m_pData;
	};
	ASSERT_SIZE(ResAccInterface, 0xc);
}
