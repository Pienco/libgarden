#pragma once

#include "NexSessionSearchCriteria.hpp"

namespace nn::pia::inet
{
	class NexSessionSearchCriteriaUnused : public NexSessionSearchCriteria
	{
	public:

		NexSessionSearchCriteriaUnused()
		{
			m_CriteriaType = 2;
		}

		virtual ~NexSessionSearchCriteriaUnused() override {}

	private:
	};
	ASSERT_SIZE(NexSessionSearchCriteriaUnused, 0xa18);
}
