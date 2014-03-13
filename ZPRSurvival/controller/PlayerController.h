#pragma once
#include "BaseController.h"
#include "../misc/EnumTypes.h"

class PlayerController : public BaseController {
public:
	PlayerController ();
	virtual ~PlayerController ();
	void setPlayerPosition (Vector2<double> position);
		//getters
	playerState getState ();

private:
	const double MAX_PLAYER_FSPEED = 300.0;
	const double MAX_PLAYER_RSPEED = 180.0;
	playerState state = IDLE;
};

