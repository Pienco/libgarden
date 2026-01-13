#pragma once

#include <nn/types.h>

namespace nw::ut
{
	struct Color8
	{
		static consteval Color8 White()
		{
			return {0xff, 0xff, 0xff, 0xff};
		}

		static consteval Color8 Black()
		{
			return {0, 0, 0, 0};
		}

		friend constexpr bool operator==(const Color8&, const Color8&) = default;

		u8 r, g, b, a;
	};
	ASSERT_SIZE(Color8, 4);
}
