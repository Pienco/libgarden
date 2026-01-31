#pragma once

#include <nn/pia/common/RootObject.hpp>

namespace nn::pia::transport
{
	class Protocol : public common::RootObject
	{
	public:
		virtual ~Protocol();

	private:
		u8 data[0x10];
	};
	ASSERT_SIZE(Protocol, 0x14);
}
