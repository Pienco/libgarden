#ifndef SSYS_MA_ALLOCATOR_HPP
#define SSYS_MA_ALLOCATOR_HPP

#include "types.h"
#include "sead/Heap.hpp"

namespace ssys::ma
{

	class Allocator
	{
	
	public:

		virtual ~Allocator();
		virtual void* Allocate(size_t size, size_t alignment);
		virtual void Free(void* p);

		inline sead::Heap* GetHeap() { return m_pHeap; }
		inline void SetHeap(sead::Heap* heap) { m_pHeap = heap; }

		static Allocator* GetGuiAllocator();
		static Allocator* GetResourceAllocator();

	private:

		sead::Heap* m_pHeap;
	};
	ASSERT_SIZE(Allocator, 8);
}

#endif
