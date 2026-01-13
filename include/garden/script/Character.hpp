#pragma once

#include <nn/types.h>

namespace script
{
	enum class Character : char16
	{
		BUTTON_A = u'\uE000',
		BUTTON_B,
		BUTTON_X,
		BUTTON_Y,
		BUTTON_L,
		BUTTON_R,
		BUTTON_DPAD,

		CLOCK,
		AMIIBO_1,
		AMIIBO_2,

		BUTTON_DPAD_UD = u'\uE07D',
		BUTTON_DPAD_LR,
	};

#define BUTTON_A u"\uE000"
#define	BUTTON_B u"\uE001"
#define	BUTTON_X u"\uE002"
#define	BUTTON_Y u"\uE003"
#define	BUTTON_L u"\uE004"
#define	BUTTON_R u"\uE005"
#define	BUTTON_DPAD u"\uE006"
#define	CLOCK u"\uE007"
#define	AMIIBO_1 u"\uE008"
#define	AMIIBO_2 u"\uE009"
#define	BUTTON_DPAD_UD u"\uE07D"
#define	BUTTON_DPAD_LR u"\uE07E"

}
