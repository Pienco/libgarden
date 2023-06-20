#ifndef SSYS_MA_LOADSPLIT_HPP
#define SSYS_MA_LOADSPLIT_HPP

#include "types.h"
#include "sead/String.hpp"
#include "sead/Heap.hpp"

namespace ssys::ma
{

	class LoadSplit
	{

	public:

		bool Read(const sead::SafeStringBase<const char>& path, sead::Heap* heap, u32 alignment = 0x80, u32 memRegion = 0x80000);

		void* GetData() const { return m_pData; }

	private:

		u8 m_Data[0xd0];
		mutable void* m_pData;
		u8 m_Data2[0x18];
	};
	ASSERT_SIZE(LoadSplit, 0xec);
}

#endif
