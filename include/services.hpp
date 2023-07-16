#ifndef HW_HPP
#define HW_HPP

#include "types.h"

extern "C" s32 GSPGPU_WriteHWRegs(u32 addr, const void* data, size_t size);

inline void lcdFillColor(bool enable, u8 r, u8 g, u8 b)
{
	const u32 data = (enable << 24) | r | (g << 8) | (b << 16);
	GSPGPU_WriteHWRegs(0x202a04, &data, 4);
}

#endif
