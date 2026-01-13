#pragma once

#include "PlayerNo.hpp"

namespace netgame
{
	class MachineBitTable
	{

	public:

		void Add(PlayerNo no);
		void Add(u8 bits);
		void Remove(PlayerNo no);
		void Reset();

		u8 GetBit() const { return m_Bit; }
		u8 GetCount() const { return m_Count; }

		bool IsSet(PlayerNo no) const { return GetMask(no) & m_Bit; }

	private:
		u8 m_Bit;
		u8 m_Count;
	};
	ASSERT_SIZE(MachineBitTable, 0x2);
}
