#ifndef G3D_RESOURCELOADER_HPP
#define G3D_RESOURCELOADER_HPP

#include "types.h"
#include "sead/String.hpp"
#include "sead/HeapMgr.hpp"
#include "nw/os/IAllocator.hpp"
#include <cstring>

namespace g3d
{

	class ResourceLoader
	{
	
	public:

		static constexpr size_t CGFX_ALIGNMENT = 0x80;


		ResourceLoader();

		void Load(const sead::SafeString* path, sead::Heap* heap, size_t alignment = CGFX_ALIGNMENT);

		inline void* Load(auto&& data, sead::Heap* heap = nullptr, size_t alignment = CGFX_ALIGNMENT)
		{
			void* const mem = sead::HeapMgr::Allocate(data.size(), heap, alignment);
			memcpy(mem, data.data(), data.size());
			SetCgfx(mem);
			return mem;
		}
		void Read(u32 area1 = 0x10000, u32 area2 = 0x10000, u32 area3 = 0x10000);
		void InitializeCgfx(nw::os::IAllocator* alloc, ResourceLoader* additional = nullptr, bool unk = true);


		inline void SetCgfx(const void* cgfx)
		{
			m_pBegin = cgfx;
			m_pCgfx = cgfx;
		}

		inline const void* const* GetCgfx()
		{
			return &m_pCgfx;
		}

	private:
		u8 m_Data[4];
		const void* m_pBegin;
		const void* m_pCgfx;
		u8 m_Data2[0xfc];
	};
	ASSERT_SIZE(ResourceLoader, 0x108);
}

#endif
