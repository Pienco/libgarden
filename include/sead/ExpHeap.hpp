#ifndef SEAD_EXPHEAP_HPP
#define SEAD_EXPHEAP_HPP

#include "sead/Heap.hpp"
#include "sead/String.hpp"

namespace sead
{

	class ExpHeap : public Heap
	{

	public:

		static ExpHeap* CreateRoot(void* addr, size_t size, const SafeString* name, bool unk = false);

	private:
	};
}

#endif
