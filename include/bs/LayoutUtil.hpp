#ifndef BS_LAYOUTUTIL_HPP
#define BS_LAYOUTUTIL_HPP

#include "font/Mgr.hpp"
#include "bs/Layout.hpp"
#include "script/RenderRuby.hpp"
#include "script/RenderGarden.hpp"
#include "ssys/ma/Allocator.hpp"
#include "sead/HeapMgr.hpp"

using FontID = font::FontID;

class ScopedAllocatorReplacement
{

public:

	using Allocator = ssys::ma::Allocator;

	inline ScopedAllocatorReplacement() : m_pGuiAllocator(Allocator::GetGuiAllocator()), m_pResourceAllocator(Allocator::GetResourceAllocator())
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

#define REPLACE_2D_UI_HEAP ScopedAllocatorReplacement replacement;

template<typename T>
concept RenderText = std::is_same_v<T, script::RenderRuby> || std::is_same_v<T, script::RenderGarden>;

class LayoutUtil
{

public:

	static inline void RegisterFont(ArcReader& reader, FontID font)
	{
		const font::Mgr* const mgr = font::Mgr::Get();
		reader.RegisterFont(mgr->GetFontName(font)->GetString(), mgr->GetFont(font));
	}

	template<RenderText T>
	static inline void SetTextBox(T& render, Layout* layout, const char* textBox)
	{
		render.SetTextBoxes(layout->FindTextBox(textBox));
	}

	template<RenderText T>
	static inline void SetText(T& render, Layout* layout, const char* textBox, const char16* text)
	{
		SetTextBox(render, layout, textBox);
		render.SetText(text);
		render.CommitText();
	}

	static inline bool SetArc(ArcReader& reader, Layout* layout, const char* name)
	{
		if (reader.ReadArc(name))
		{
			layout->SetArcResAccReader(&reader);
			return true;
		}
		return false;
	}

	static inline void BindAnimation(Pane* pane, Animation* anim, bool recursive, bool disable = false)
	{
		pane->BindAnimation(anim->GetNwAnim(), recursive, disable);
	}

	static inline void UnbindAnimation(Pane* pane, Animation* anim, bool recursive)
	{
		pane->UnbindAnimation(anim->GetNwAnim(), recursive);
	}
};

#endif
