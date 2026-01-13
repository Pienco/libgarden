#pragma once

#include <nn/pia/types.hpp>

namespace nn::pia::session
{

	class SessionSearchCriteria
	{

	public:

		virtual ~SessionSearchCriteria() {}

	protected:

		u8 m_CriteriaType;
		u32 unk[2];
	};
	static_assert(sizeof(SessionSearchCriteria) == 0x10);
}
