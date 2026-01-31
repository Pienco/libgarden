#pragma once

#include <nn/pia/common/RootObject.hpp>

namespace nn::pia::transport
{
	class IdentificationInfo : public common::RootObject
	{

	private:
		u8 data[0x4c];
	};
	static_assert(sizeof(IdentificationInfo) == 0x4c);
}
