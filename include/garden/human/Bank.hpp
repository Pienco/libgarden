#pragma once

#include "../ssys/ma/HeapAllocator.hpp"

template<size_t U1, size_t U2, size_t U3, size_t U4, bool U5>
struct BankVramConfig
{

};

using EmptyBankVramConfig = BankVramConfig<0u, 0u, 0u, 0u, false>;

template<size_t HeapSize, size_t AllocatorCount, bool UnknownBool, typename VramConfig>
class Bank
{
public:
	virtual ~Bank();
	virtual bool Vfun_8(size_t index);

protected:
	ssys::ma::HeapAllocator m_Allocators[AllocatorCount];
	void* m_pVramAHeaps[AllocatorCount];
	void* m_pVramBHeaps[AllocatorCount];
};
static_assert(sizeof(Bank<10240u, 1u, false, EmptyBankVramConfig>) == 0x14);
