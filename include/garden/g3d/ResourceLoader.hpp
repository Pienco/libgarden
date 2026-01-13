#ifndef G3D_RESOURCELOADER_HPP
#define G3D_RESOURCELOADER_HPP

#include "../ssys/ma/LoadSplit.hpp"

#include <sead/String.hpp>
#include <sead/new.hpp>
#include <nw/os/IAllocator.hpp>

#include <cstring>

namespace g3d
{

	class ResourceLoader
	{
	
	public:

		static constexpr size_t CGFX_ALIGNMENT = 0x80;

		ResourceLoader();

		bool Load(const sead::SafeString& path, sead::Heap* heap, size_t alignment = CGFX_ALIGNMENT);
		bool LoadAsync(const sead::SafeString& path, sead::Heap* heap, size_t alignment = CGFX_ALIGNMENT);
		bool LoadBuffered(const sead::SafeString& path, sead::Heap* heap, size_t alignment = CGFX_ALIGNMENT)
		{
			const auto result = m_Loader.LoadBuffered(path, heap, alignment);
			if (result && m_pBegin == nullptr)
				SetCgfx(m_Loader.GetData());
			return result;
		}

		void* Load(auto&& data, sead::Heap* heap = nullptr, size_t alignment = CGFX_ALIGNMENT)
		{
			void* const mem = sead::AllocBuffer(data.size(), heap, alignment);
			memcpy(mem, data.data(), data.size());
			SetCgfx(mem);
			return mem;
		}
		void Read(u32 area1 = 0x10000, u32 area2 = 0x10000, u32 area3 = 0x10000);
		void InitializeCgfx(nw::os::IAllocator* alloc, ResourceLoader* additional = nullptr, bool unk = true);

		void SetCgfx(const void* cgfx)
		{
			m_pBegin = cgfx;
			m_pCgfx = cgfx;
		}

		const void* const* GetCgfx()
		{
			return &m_pCgfx;
		}

	private:
		u8 m_Data[4];
		const void* m_pBegin;
		const void* m_pCgfx;
		const void* m_pCgfx2;
		void* m_pVramA;
		void* m_pVramB;
		sead::Heap* m_pHeap;
		ssys::ma::LoadSplit m_Loader;
	};
	ASSERT_SIZE(ResourceLoader, 0x108);
}

#endif
