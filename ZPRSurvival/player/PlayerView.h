#pragma once
#include "../animated/AnimatedObjectView.h"
#include "../interface/TextureHolder.h"

class PlayerView : public AnimatedObjectView {
public:
	PlayerView ();
	virtual ~PlayerView ();

private:
	TextureHolder textureHolder;
};

