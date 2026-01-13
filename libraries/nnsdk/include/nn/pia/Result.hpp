#pragma once

#include <nn/pia/types.hpp>

namespace nn::pia
{

	class Result
	{
	public:

		constexpr operator bool() const { return m_Value == 0; }

	private:
		s32 m_Value {};
	};
	static_assert(sizeof(Result) == 4);
}
