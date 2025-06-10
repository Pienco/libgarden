#ifndef SSYS_MA_ALLOCATOR_HPP
#define SSYS_MA_ALLOCATOR_HPP

#include "types.h"
#include "sead/Heap.hpp"
#include "nw/os/IAllocator.hpp"

namespace ssys::ma
{

	class Allocator : public nw::os::IAllocator
	{
	
	public:

		constexpr Allocator() : m_pHeap { } { }
		constexpr Allocator(sead::Heap* heap) : m_pHeap { heap } { }
		virtual ~Allocator() override;
		virtual void* Allocate(size_t size, size_t alignment) override;
		virtual void Free(void* p) override;

		sead::Heap* GetHeap() { return m_pHeap; }
		void SetHeap(sead::Heap* heap) { m_pHeap = heap; }

		static Allocator* GetGuiAllocator();
		static Allocator* GetResourceAllocator();

	private:

		sead::Heap* m_pHeap;
	};
	ASSERT_SIZE(Allocator, 8);
}

#endif
