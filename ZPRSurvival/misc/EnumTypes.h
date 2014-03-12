#pragma once
enum gameState {
	UNKNOWN = 0,
	INIT,
	IN_MENU,
	PLAYING,
	PAUSE
};

enum movingDirection {
	UP = 1,
	RIGHT = 2,
	DOWN = 4,
	LEFT = 8
};

enum playerState {
	IDLE = 0,
	MOVING,
	USING_ITEM,
	CRAFTING,
};
