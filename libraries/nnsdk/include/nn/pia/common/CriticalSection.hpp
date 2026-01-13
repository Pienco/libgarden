#pragma once

#include <nn/os/CriticalSection.hpp>

namespace nn::pia::common
{
	class CriticalSection
	{
	public:
		void Lock();
		void Unlock();

	private:
		os::CriticalSection m_CriticalSection;
	};
	static_assert(sizeof(CriticalSection) == 0xc);
}
