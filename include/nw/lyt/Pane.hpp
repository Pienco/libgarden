#ifndef NW_LYT_PANE_HPP
#define NW_LYT_PANE_HPP

#include "nw/lyt/PaneBase.hpp"
#include "nw/lyt/Material.hpp"
#include "math/Vector.hpp"

namespace nw::lyt
{

	class Pane : PaneBase
	{

	public:


		virtual ~Pane() override;
		virtual void GetType();
		virtual void GetVertexColor();
		virtual void SetVertexColor();
		virtual void GetColorComponent();
		virtual void SetColorComponent();
		virtual void GetVertexColorComponent();
		virtual void SetVertexColorComponent();
		virtual void GetMaterialNum();
		virtual Material* GetMaterial(size_t = 0);
		virtual Pane* FindPane(const char* name, bool recursive = true);
		virtual Material* FindMaterial();
		virtual void Animate(u32 options);
		virtual void AnimateSelf(u32 options);
		virtual void BindAnimation(void* anim, bool recursive, bool disable);
		virtual void UnbindAnimation(void* anim, bool recursive);


		inline void SetVisible(bool visible = true)
		{
			m_Flags = visible ? m_Flags | 1 : m_Flags & (u8)(~1u);
		}
		inline void SetMatrixDirty() { m_Flags &= 0xcf; }
		inline math::Vector3& GetTranslation() { return m_Translation; }
		inline const math::Vector3& GetTranslation() const { return m_Translation; }
		inline math::Vector3 GetGlobalTranslation() const { return m_GlobalMatrix.column<3>(); }
		inline void SetTranslation(const math::Vector3& translation) { m_Translation = translation; }
		inline Pane* GetParent() { return m_pParent; }

		void AppendChild(Pane* child);
		void RemoveChild(Pane* child);


	private:

		Pane* m_pParent;
		u8 m_Data[0x18];
		math::Vector3 m_Translation;
		math::Vector3 m_Rotation;
		math::Vector2 m_Scale;
		math::Vector2 m_Size;
		math::Matrix34 m_Matrix;
		math::Matrix34 m_GlobalMatrix;
		void* m_pUnk0;
		u8 m_Alpha;
		u8 m_GlobalAlpha;
		u8 m_Origin;
		u8 m_Flags;
		u8 m_Data2[0x1c];
	};
	ASSERT_SIZE(Pane, 0xd4);
}

#endif
