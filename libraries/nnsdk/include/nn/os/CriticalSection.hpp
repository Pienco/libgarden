#pragma once

#include <cstdint>

namespace nn::os
{
	class CriticalSection
	{
	public:

		void Enter();
		void Exit();

	private:
		uint8_t data[0xc];
	};
	static_assert(sizeof(CriticalSection) == 0xc);
}
