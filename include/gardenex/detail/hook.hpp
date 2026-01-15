#pragma once

#include <nn/types.h>

#include <array>

#ifdef GARDENEX_CHECK_EMULATOR

extern "C" void svcInvalidateInstructionCacheRange(void*, u32);

namespace gardenex
{
	bool IsEmulator();
}

#endif

namespace gardenex::detail
{

	template<bool Link = false>
	constexpr u32 MakeArmBranch(u32 src, u32 dst)
	{
		constexpr u32 instrBase = Link ? 0xEB000000 : 0xEA000000;
		u32 off = dst - (src + 8);
		return instrBase | ((off >> 2) & 0xFFFFFF);
	}

	constexpr std::array<u32, 2> MakeArmLongJump(u32 dst) { return {0xe51ff004, dst}; }

	inline void Hook(u32 target, u32 callback)
	{
		*(std::array<u32, 2>*)target = MakeArmLongJump(callback);
		#ifdef GARDENEX_CHECK_EMULATOR
		if (IsEmulator())
			svcInvalidateInstructionCacheRange((void*)target, sizeof(std::array<u32, 2>));
		#endif
	}

	inline void Hook(auto target, auto callback)
	{
		Hook((u32)target, (u32)callback);
	}
}
