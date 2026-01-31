#pragma once

#include "nw/lyt/PaneBase.hpp"
#include "nw/lyt/Material.hpp"
#include "nw/lyt/Drawer.hpp"
#include "nw/lyt/DrawInfo.hpp"
#include "nn/math/Vector.hpp"

#include <utility>

namespace nw::lyt
{
	class Pane : protected PaneBase
	{
	public:
		enum class OriginX : u8
		{
			LEFT,
			CENTER,
			RIGHT,
		};

		enum class OriginY : u8
		{
			TOP,
			CENTER,
			BOTTOM,
		};

		Pane(const void* res);

		constexpr Pane(nn::math::VEC2 size = {1.0f, 1.0f}, Pane* parent = nullptr) :
			m_pParent {parent},
			m_Size {size}
		{ }

		virtual ~Pane() override;
		virtual void GetRuntimeTypeInfo();
		virtual void GetVertexColor();
		virtual void SetVertexColor();
		virtual void GetColorComponent();
		virtual void SetColorComponent();
		virtual void GetVertexColorComponent();
		virtual void SetVertexColorComponent();
		virtual void GetMaterialNum();
		virtual Material* GetMaterial(size_t = 0);
		virtual Pane* FindPane(const char* name, bool recursive = true);
		virtual Material* FindMaterial(const char* name, bool recursive = true);
		virtual void Animate(u32 options);
		virtual void AnimateSelf(u32 options);
		virtual void BindAnimation(void* anim, bool recursive, bool disable);
		virtual void UnbindAnimation(void* anim, bool recursive);
		virtual void Unk_44();
		virtual void UnbindAnimationSelf(void* anim);
		virtual void Unk_4c();
		virtual void Unk_50();
		virtual void Unk_54();
		virtual void Unk_58();
		virtual void CalculateMtx(const DrawInfo& info);
		virtual void Unk_60();
		virtual void Unk_64();
		virtual u32* MakeUniformDataSelf(u32* cmdbuf, DrawInfo& info, Drawer& drawer);
		virtual void Unk_6c();

		OriginX GetOriginX() const { return GetOriginX(m_Origin); }
		OriginY GetOriginY() const { return GetOriginY(m_Origin); }

		void SetOrigin(OriginX x, OriginY y) { m_Origin = EncodeOrigin(x, y); }

		void SetVisible(bool visible = true)
		{
			m_Flags = visible 
				? m_Flags | VISIBLE 
				: m_Flags & (u8)(~VISIBLE);
		}

		bool IsVisible() const { return m_Flags & VISIBLE; }

		void SetMatrixDirty() { m_Flags &= 0xcf; }
		nn::math::VEC3& GetTranslation() { return m_Translation; }
		const nn::math::VEC3& GetTranslation() const { return m_Translation; }
		nn::math::VEC3 GetGlobalTranslation() const
		{ 
			return {m_GlobalMatrix.data[0][3], m_GlobalMatrix.data[1][3], m_GlobalMatrix.data[2][3]};
		}
		void SetTranslation(const nn::math::VEC3& translation) { m_Translation = translation; }

		const auto& GetGlobalMatrix() const { return m_GlobalMatrix; }

		void SetMatrix(const auto& matrix)
		{
			m_GlobalMatrix = matrix;
		}

		Pane* GetParent() { return m_pParent; }
		void AppendChild(Pane* child);
		void RemoveChild(Pane* child);

	protected:

		u8 GetOrigin() const { return m_Origin; }

		OriginX GetOriginX(u8 value) const { return static_cast<OriginX>(value % 3u); }
		OriginY GetOriginY(u8 value) const { return static_cast<OriginY>(value / 3u); }

		u8 EncodeOrigin(OriginX x, OriginY y)
		{
			return static_cast<u8>(std::to_underlying(x) + std::to_underlying(y) * 3u);
		} 

	private:
		enum Flags : u8
		{
			VISIBLE = 1,
			INFLUENCED_ALPHA = 2,
			LOCATION_ADJUST = 4,
		};

		Pane* m_pParent;
		ut::LinkList<&Pane::m_Node> m_Children;
		u8 m_Anims[0xc] {};
		nn::math::VEC3 m_Translation {};
		nn::math::VEC3 m_Rotation {};
		nn::math::VEC2 m_Scale {1.0f, 1.0f};
		nn::math::VEC2 m_Size;
		nn::math::MTX34 m_Matrix {};
		nn::math::MTX34 m_GlobalMatrix {};
		void* m_pUnk0 {};
		u8 m_Alpha {0xff};
		u8 m_GlobalAlpha {0xff};
		u8 m_Origin {std::to_underlying(OriginX::LEFT) + std::to_underlying(OriginY::TOP) * 3u};
		u8 m_Flags {VISIBLE};
		char m_Name[17] {};
		char m_Data[9] {};
	};
	ASSERT_SIZE(Pane, 0xd4);
}
