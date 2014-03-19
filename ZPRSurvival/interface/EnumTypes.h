#pragma once
enum GameState {
	UNKNOWN = 0,
	INIT,
	IN_MENU,
	PLAYING,
	PAUSE,
	EXIT
};

enum PlayerState {
	IDLE = 0,
	MOVING,
	USING_ITEM,
	CRAFTING,
};

enum MovingDirection {
	UP = 1,
	RIGHT = 2,
	DOWN = 4,
	LEFT = 8
};

enum MovingPhase {
	STOP = 0,
	ACCEL_FWD = 1,
	ACCEL_BWD = 2,
	DECEL_FWD = 4,
	DECEL_BWD = 8
};
