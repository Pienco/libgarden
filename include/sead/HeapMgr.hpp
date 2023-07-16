#ifndef SEAD_HEAPMGR_HPP
#define SEAD_HEAPMGR_HPP

#include "sead/ExpHeap.hpp"

namespace sead
{

	class HeapMgr
	{

	public:

		static Heap* GetCurrentHeap();

		static inline Heap* GetRootHeap()
		{
			return (Heap*)0x30000000; // s_ppRootHeaps[0];
		}

		static inline Heap* GetSystemHeap()
		{
			return s_pSystemHeap;
		}

		static inline Heap* GetCustomHeap()
		{
			return (Heap*)s_pCustomHeap;
		}

		static inline void InitializeCustom()
		{
			static constexpr SafeString s {"Heap"};
			ExpHeap::CreateRoot((void*)s_pCustomHeap, 0x331b8000 - s_pCustomHeap, &s);
		}

		static void* Allocate(size_t size, Heap* heap = nullptr, size_t alignment = sizeof(size_t));

	private:

		static constexpr u32 s_pCustomHeap = 0x33148000;
		// static Heap** s_ppRootHeaps;
		static Heap* s_pSystemHeap;

	};
}

#endif
