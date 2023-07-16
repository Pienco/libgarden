#ifndef BS_LYTUTIL_HPP
#define BS_LYTUTIL_HPP

#include "font/Mgr.hpp"
#include "bs/Layout.hpp"
#include "script/RenderRuby.hpp"
#include "script/RenderGarden.hpp"
#include "ssys/ma/Allocator.hpp"
#include "sead/HeapMgr.hpp"
#include <cstring>


#define REPLACE_2D_UI_HEAP ::lytutil::ScopedAllocatorReplacement allocatorReplacement;

namespace lytutil
{

	class ScopedAllocatorReplacement
	{

	public:

		using Allocator = ssys::ma::Allocator;

		inline ScopedAllocatorReplacement(): m_pGuiAllocator(Allocator::GetGuiAllocator()), m_pResourceAllocator(Allocator::GetResourceAllocator())
		{
			m_pGuiHeap = m_pGuiAllocator->GetHeap();
			m_pResourceHeap = m_pResourceAllocator->GetHeap();

			sead::Heap* const heap = sead::HeapMgr::GetSystemHeap();
			m_pGuiAllocator->SetHeap(heap);
			m_pResourceAllocator->SetHeap(heap);
		}

		inline ~ScopedAllocatorReplacement()
		{
			m_pGuiAllocator->SetHeap(m_pGuiHeap);
			m_pResourceAllocator->SetHeap(m_pResourceHeap);
		}

	private:

		Allocator* m_pGuiAllocator;
		Allocator* m_pResourceAllocator;
		sead::Heap* m_pGuiHeap;
		sead::Heap* m_pResourceHeap;

	};

	template<typename T>
	concept RenderText = std::is_same_v<T, script::RenderRuby> || std::is_same_v<T, script::RenderGarden>;
	
	inline void RegisterFont(ArcReader& reader, font::FontID font)
	{
		const font::Mgr* const mgr = font::Mgr::Get();
		reader.RegisterFont(mgr->GetFontName(font)->GetString(), mgr->GetFont(font));
	}

	template<RenderText T>
	inline void SetTextBox(T& render, Layout* layout, const char* textBox)
	{
		render.SetTextBoxes(layout->FindTextBox(textBox));
	}

	template<RenderText T>
	inline void SetText(T& render, Layout* layout, const char* textBox, const char16* text)
	{
		SetTextBox(render, layout, textBox);
		render.SetText(text);
		render.CommitText();
	}

	inline bool SetArc(ArcReader& reader, Layout* layout, const char* name)
	{
		if (reader.ReadArc(name))
		{
			layout->SetArcResAccReader(&reader);
			return true;
		}
		return false;
	}

	inline bool SetArc(ArcReader& reader, Layout* layout, const void* data)
	{
		if (reader.SetArc(data))
		{
			layout->SetArcResAccReader(&reader);
			return true;
		}
		return false;
	}

	inline void* AllocateArcMemory(auto&& data)
	{
		void* const mem = sead::HeapMgr::Allocate(data.size(), nullptr, 0x80);
		memcpy(mem, data.data(), data.size());
		return mem;
	}

	inline void BindAnimation(Pane* pane, Animation* anim, bool recursive, bool disable = false)
	{
		pane->BindAnimation(anim->GetNwAnim(), recursive, disable);
	}

	inline void UnbindAnimation(Pane* pane, Animation* anim, bool recursive)
	{
		pane->UnbindAnimation(anim->GetNwAnim(), recursive);
	}
};

#endif
