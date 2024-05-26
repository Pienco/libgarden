#ifndef NW_LYT_PICTURE_HPP
#define NW_LYT_PICTURE_HPP

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

#endif
