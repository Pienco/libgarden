#pragma once

#include <nw/lyt/TexMap.hpp>
#include <nw/ut/Color.hpp>

namespace nw::lyt
{
	class Material final
	{
	public:

		constexpr Material(bool userOwned) :
			m_Flags {userOwned ? u8 {1} : u8 {0}}
		{ }

		virtual ~Material();

		void SetTexture(size_t index, const TextureInfo& info)
		{
			((TexMap*)m_pElements)[index].Set(info);
			m_Flags &= 0xfb;
		}

	private:
		u8 data[0xc] {};
		ut::Color8 m_Colors[7] 
		{
			ut::Color8::Black(),
			ut::Color8::White(),
			ut::Color8::White(),
			ut::Color8::White(),
			ut::Color8::White(),
			ut::Color8::White(),
			ut::Color8::White()
		};
		u32 m_Capacity {};
		u32 m_Count {};
		void* m_pElements {};
		char m_Name[21] {};
		u8 m_Flags {};
	};
	ASSERT_SIZE(Material, 0x50);
}
