#pragma once

#include "nw/lyt/Pane.hpp"

namespace nw::lyt
{

	class Picture final : public Pane
	{
	public:
		Material* GetMaterial(size_t = 0) override;

	private:
	};
}
