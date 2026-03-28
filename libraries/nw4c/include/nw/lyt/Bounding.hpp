#pragma once

#include <nw/lyt/Pane.hpp>

namespace nw::lyt
{
	class Bounding : public Pane
	{
	public:
		using Pane::Pane;

		virtual ~Bounding() override;

	};
	ASSERT_SIZE(Bounding, 0xd4);
}
