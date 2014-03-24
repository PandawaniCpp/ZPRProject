#pragma once
#include "../animated/AnimatedObjectView.h"
#include "../interface/ResourceHolder.h"
#include "../interface/ResourcesID.h"

class PlayerView : public AnimatedObjectView {
public:
	PlayerView ();
	virtual ~PlayerView ();

private:
	ResourceHolder<Texture, Textures::ID> textureHolder;
};

