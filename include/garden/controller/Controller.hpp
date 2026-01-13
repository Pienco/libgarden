#pragma once

#include "../types.hpp"

#include <sead/math/Vector.hpp>

class Controller
{
public:
	enum Pad : u32
	{
		A = 1 << 0,
		B = 1 << 1,
		X = 1 << 3,
		Y = 1 << 4,

		START = 1 << 11,
		SELECT = 1 << 12,

		L = 1 << 13,
		R = 1 << 14,
		TOUCH = 1 << 15,
		DPAD_UP = 1 << 16,
		DPAD_DOWN = 1 << 17,
		DPAD_LEFT = 1 << 18,
		DPAD_RIGHT = 1 << 19,

		CPAD_UP = 1 << 20,
		CPAD_DOWN = 1 << 21,
		CPAD_LEFT = 1 << 22,
		CPAD_RIGHT = 1 << 23,

		RIGHT = DPAD_RIGHT | CPAD_RIGHT,
		LEFT = DPAD_LEFT | CPAD_LEFT,
		UP = DPAD_UP | CPAD_UP,
		DOWN = DPAD_DOWN | CPAD_DOWN,

		DPAD = DPAD_RIGHT | DPAD_LEFT | DPAD_UP | DPAD_DOWN,
		CPAD = CPAD_RIGHT | CPAD_LEFT | CPAD_UP | CPAD_DOWN,

		DIR = RIGHT | LEFT | UP | DOWN,
	};

	static bool IsTrig(u32 mask);
	static bool IsHold(u32 mask);
	static bool IsHoldAll(u32 mask);
	static bool IsRelease(u32 mask);
	static bool IsRepeat(u32 mask);
	static const sead::Vector2f& GetCirclePad();
};
