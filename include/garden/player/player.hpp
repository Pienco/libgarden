#pragma once

#include "PlayerState.hpp"
#include "../ac/AcPlayer.hpp"


/**
 * @return PlayerState of `player`. Returns state of player 0 if `player` is invalid. Never returns `nullptr`.
 */
PlayerState* PlayerGetState(netgame::PlayerNo player = netgame::PlayerNo::INVALID);

AcPlayer* PlayerGetActor(netgame::PlayerNo player, bool skipCheck = true);
inline AcPlayer* PlayerGetMyActor(bool skipCheck = true) { return PlayerGetActor(netgame::PlayerNo::MY_NO, skipCheck); }
bool PlayerGetPosition(s32& x, s32& y, netgame::PlayerNo no = netgame::PlayerNo::MY_NO, bool skipCheck = true);
const Vector3* PlayerGetPositionForCamera();
