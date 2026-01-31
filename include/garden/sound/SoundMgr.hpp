#pragma once

#include <nn/types.h>

enum class SeID : u32
{
	SELECT_ICON = 0x1000399,
	SELECT_TAB = 0x10003f1,
	OK_TAB = 0x10003f2,
	OK_TAB_OUT = 0x10003f3,
	MENU_TAB_MENU_IN = 0x10003f4,
	OPEN_PRESENT = 0x1000407,
	BOOK_ICON_SELECT_OK = 0x1000413,
	NEW_PLAYER_JOINED = 0x100043e,
};

class SoundMgr
{

public:

	static void PlaySound(SeID id, float param = 0.0f);

private:

};
