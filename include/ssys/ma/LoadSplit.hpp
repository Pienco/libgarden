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

		bool Load(const sead::SafeStringBase<const char>& path, sead::Heap* heap, size_t alignment = 0x80, size_t buffer = 0x80000);
		bool LoadBuffered(const sead::SafeString& path, sead::Heap* heap, size_t alignment = 0x80);

		void* GetData() const { return m_pData; }

	private:

		u8 m_Data[0xd0];
		mutable void* m_pData;
		u8 m_Data2[0x18];
	};
	ASSERT_SIZE(LoadSplit, 0xec);
}

#endif
