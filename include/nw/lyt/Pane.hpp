#ifndef NW_LYT_PANE_HPP
#define NW_LYT_PANE_HPP

#include "nw/lyt/PaneBase.hpp"
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
		virtual void GetMaterial();
		virtual void FindPane();
		virtual void FindMaterial();
		virtual void Animate(u32 options);
		virtual void AnimateSelf(u32 options);
		virtual void BindAnimation(void* anim, bool recursive, bool disable);
		virtual void UnbindAnimation(void* anim, bool recursive);


		inline void SetVisible(bool visible)
		{
			m_Flags = visible ? m_Flags | 1 : m_Flags & (u8)(~1u);
		}
		inline void SetMatrixDirty() { m_Flags &= 0xcf; }
		inline Vector3& GetTranslation() { return m_Translation; }
		inline const Vector3* GetTranslation() const { return &m_Translation; }
		inline void SetTranslation(const Vector3& translation) { m_Translation = translation; }
		inline Pane* GetParent() { return m_pParent; }

		void AppendChild(Pane* child);
		void RemoveChild(Pane* child);


	private:

		Pane* m_pParent;
		u8 m_Data[0x18];
		Vector3 m_Translation;
		Vector3 m_Rotation;
		Vector2 m_Scale;
		Vector2 m_Size;
		Matrix34 m_Matrix;
		Matrix34 m_GlobalMatrix;
		void* m_pUnk0;
		u8 m_Alpha;
		u8 m_GlobalAlpha;
		u8 m_Origin;
		u8 m_Flags;
		u8 m_Data2[0x1c];
	};
	static constexpr size_t si = sizeof(Pane);
	ASSERT_SIZE(Pane, 0xd4);
}

#endif
