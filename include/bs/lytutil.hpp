#ifndef BS_LYTUTIL_HPP
#define BS_LYTUTIL_HPP

#include "font/Mgr.hpp"
#include "bs/Layout.hpp"
#include "script/RenderRuby.hpp"
#include "script/RenderGarden.hpp"
#include "ssys/ma/Allocator.hpp"
#include "sead/new.hpp"
#include "sead/HeapMgr.hpp"

#include <memory>

#define REPLACE_2D_UI_HEAP ::lytutil::ScopedAllocatorReplacement allocatorReplacement;

template<std::array Data>
class ArcResource
{

public:

	inline const void* Get() { return m_Data.get(); }

private:

	using Type = std::decay_t<decltype(Data)>;
	std::unique_ptr<Type> m_Data { new (nullptr, 0x80) Type { Data } };
};

template<std::array Data, size_t AnimationCount>
struct ArcComponents
{
	template<const char* LayoutName, std::array<const char*, AnimationCount> AnimationNames = { }>
	inline void Initialize(u8 layer)
	{
		reader.SetArc(resource.Get());
		layout.SetArcResAccReader(&reader);

		layout.Build(LayoutName);
		layout.SetLayer(layer);

		for (size_t i = 0; i < AnimationCount; i++)
			animations[i].Initialize(AnimationNames[i], &reader);
	}

	inline bool AnimateNext(size_t animIndex)
	{
		auto& anim = animations[animIndex];
		if (!anim.IsDone())
		{
			anim.IncreaseFrame();
			layout.Animate();
			return false;
		}
		return true;
	}

	ArcResource<Data> resource;
	ArcReader reader;
	Layout layout;
	std::array<Animation, AnimationCount> animations;
};

namespace lytutil
{

	class ScopedAllocatorReplacement
	{

	public:

		using Allocator = ssys::ma::Allocator;

		inline ScopedAllocatorReplacement(sead::Heap* heap = sead::HeapMgr::GetSystemHeap()) 
			: m_pGuiAllocator(Allocator::GetGuiAllocator()), m_pResourceAllocator(Allocator::GetResourceAllocator())
		{
			m_pGuiHeap = m_pGuiAllocator->GetHeap();
			m_pResourceHeap = m_pResourceAllocator->GetHeap();

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
	inline void SetText(T& render, TextBox* textBox, const char16* text)
	{
		render.SetTextBoxes(textBox);
		render.SetText(text);
		render.CommitText();
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
