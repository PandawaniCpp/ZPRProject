#pragma once
#include "../animated/AnimatedObjectView.h"
#include "../interface/ResourceHolder.h"
#include "../interface/ResourcesID.h"

class PlayerView : public AnimatedObjectView {
public:
	PlayerView ();
	virtual ~PlayerView ();

	virtual void draw (sf::RenderWindow& window) const;

private:
	ResourceHolder<Texture, Textures::ID> textureHolder;
};

