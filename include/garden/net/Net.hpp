#pragma once

#include "nex/Framework.hpp"

namespace net
{
	class Net
	{
	public:
		static Net* Get() { return &s_Instance; }

		nex::Framework* GetFramework() { return m_pFramework; }

		bool Connect(bool local);
		bool CreateOrJoinRandomSession(u32);

		bool Stub0(u32 param)
		{
			if (m_pFramework == nullptr) return false;
			return m_pFramework->Stub0(param);
		}

		bool IsError() const;

	private:
		u8 data[0xb8];
		nex::Framework* m_pFramework;

		static Net s_Instance;
	};
}
