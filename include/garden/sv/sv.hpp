#pragma once

#include "SvGardenPlus.hpp"
#include "../player/PlayerSaveNumber.hpp"

SvPlayer* SvGetCurrentPlayer();
PlayerSaveNumber SvGetPlayerSaveNo(netgame::PlayerNo player = netgame::PlayerNo::MY_NO);
bool SvIsValidPlayerSaveNo(PlayerSaveNumber save);
SvPlayer* SvGetPlayer(PlayerSaveNumber save);
SvPlayer* SvGetNetPlayer(netgame::PlayerNo player = netgame::PlayerNo::MY_NO);
