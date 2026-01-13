#pragma once

#include "../sv/SvPlayer.hpp"
#include "../netgame/PlayerNo.hpp"

enum class PlayerSaveNumber : u8
{
	VILLAGE_PLAYER_0,
	VILLAGE_PLAYER_1,
	VILLAGE_PLAYER_2,
	VILLAGE_PLAYER_3,
	NET_PLAYER_0,
	NET_PLAYER_1,
	NET_PLAYER_2,
	NET_PLAYER_3,
	INVALID
};
 
PlayerSaveNumber GetSvPlayerNo(netgame::PlayerNo id);
SvPlayer* GetSvPlayer(PlayerSaveNumber no);
