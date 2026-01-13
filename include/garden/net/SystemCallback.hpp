#pragma once

#include <nn/pia/types.hpp>

namespace net
{
	class SystemCallback
	{
	public:
		using StationId = nn::pia::StationId;

		virtual ~SystemCallback();

	private:
	};
	ASSERT_SIZE(SystemCallback, 4);
}
