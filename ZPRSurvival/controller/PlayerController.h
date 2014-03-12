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
	playerState state = IDLE;
};

