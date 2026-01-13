#pragma once

namespace nn::pia::transport
{
	class IdentificationInfoTable
	{
	public:

		static IdentificationInfoTable* Get() { return s_pInstance; }

	private:

		static IdentificationInfoTable* s_pInstance;
	};
}
