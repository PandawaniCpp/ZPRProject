#pragma once
#include "SFML/Graphics.hpp"
#include "PerlinNoise.h"

using namespace sf;

class MapTile : public Sprite {
public:
	//MapTile();
	MapTile();
	~MapTile();
	//virtual void draw(RenderTarget& target) const;
private:
	bool initialized;
};

