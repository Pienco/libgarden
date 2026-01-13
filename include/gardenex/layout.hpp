#pragma once

#include <nw/lyt/TextBox.hpp>
#include <garden/font/Mgr.hpp>
#include <garden/ssys/ma/lyt/LayoutMgr.hpp>
#include <garden/script/RenderMain.hpp>

namespace gardenex
{
	namespace detail
	{
		inline constinit nw::lyt::Material dummyMaterial {true};
		inline constinit nw::lyt::DrawInfo dummyDrawInfo {};
	}

	inline nw::lyt::TextBox CreateTextBox(math::Vector2 size, u16 maxCharCount, const char16* text, u16 length)
	{
		return {size, font::Mgr::Get()->GetFont(font::GARDEN_MSG_16), maxCharCount, text, length, &detail::dummyMaterial};
	}

	inline nw::lyt::DrawInfo& GetDummyDrawInfo()
	{
		detail::dummyDrawInfo.SetGraphicsResource(&ssys::ma::lyt::LayoutMgr::Get()->GetResource());
		return detail::dummyDrawInfo;
	}

	inline script::RenderMain& GetDummyTagProcessor()
	{
		static script::RenderMain dummyTagProcessor {};
		return dummyTagProcessor;
	}

	inline nn::math::MTX44& GetProjectionMatrix(bool bottomScreen, bool forTextWriter)
	{
		static constexpr float h = 240.0f;
		static constexpr float v01[] {-2.0f / h, 2.0f / h};
		static constexpr float v10[] {-2.0f / 320.0f, -2.0f / 400.0f};
		static constinit auto matrix = []
		{
			constexpr float n = 500.0f;
			constexpr float f = -1500.0f;
			nn::math::MTX44 m {};
			auto& v = m.data;
			v[0][1] = v01[0];
			v[1][0] = v10[0];
			v[0][3] = 1.0f;
			v[1][3] = 1.0f;
			v[2][2] = -2.0f / (f - n);
			v[2][3] = -(f + n) / (f - n);
			v[3][3] = 1.0f;
			return m;
		}();
		matrix.data[0][1] = forTextWriter ? v01[0] : v01[1];
		matrix.data[1][0] = bottomScreen ? v10[0] : v10[1];
		matrix.data[0][3] = forTextWriter ? 1.0f : 0.0f;
		matrix.data[1][3] = forTextWriter ? 1.0f : 0.0f;
		return matrix;
	};
}
