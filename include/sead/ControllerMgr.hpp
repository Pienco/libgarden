#ifndef SEAD_CONTROLLERMGR_HPP
#define SEAD_CONTROLLERMGR_HPP

#include "types.h"

namespace sead
{

	enum Key : u32
	{
		KEY_A = 1 << 0,
		KEY_B = 1 << 1,
		KEY_X = 1 << 3,
		KEY_Y = 1 << 4,

		KEY_START = 1 << 11,
		KEY_SELECT = 1 << 12,

		KEY_L = 1 << 13,
		KEY_R = 1 << 14,

		KEY_DPAD_UP = 1 << 16,
		KEY_DPAD_DOWN = 1 << 17,
		KEY_DPAD_LEFT = 1 << 18,
		KEY_DPAD_RIGHT = 1 << 19,

		KEY_CPAD_UP = 1 << 20,
		KEY_CPAD_DOWN = 1 << 21,
		KEY_CPAD_LEFT = 1 << 22,
		KEY_CPAD_RIGHT = 1 << 23,

		KEY_COUNT = 18,

		KEY_RIGHT = KEY_DPAD_RIGHT | KEY_CPAD_RIGHT,
		KEY_LEFT = KEY_DPAD_LEFT | KEY_CPAD_LEFT,
		KEY_UP = KEY_DPAD_UP | KEY_CPAD_UP,
		KEY_DOWN = KEY_DPAD_DOWN | KEY_CPAD_DOWN,

		KEY_DPAD = KEY_DPAD_RIGHT | KEY_DPAD_LEFT | KEY_DPAD_UP | KEY_DPAD_DOWN,
		KEY_CPAD = KEY_CPAD_RIGHT | KEY_CPAD_LEFT | KEY_CPAD_UP | KEY_CPAD_DOWN,

		KEY_DIR = KEY_RIGHT | KEY_LEFT | KEY_UP | KEY_DOWN,
	};

	class ControllerMgr
	{

	public:

		static bool IsPressed(u32 keys);
		static bool IsHeld(u32 keys);
		static bool IsReleased(u32 keys);

	private:

	};
}

#endif
