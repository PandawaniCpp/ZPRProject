#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;

class MapTile :	public Drawable, public Transformable {
public:
	MapTile();
	MapTile(int size, Texture tile);
	~MapTile();
	bool isInitilaized();
	virtual void draw(RenderTarget& target, RenderStates states) const;
private:
	bool initialized;
	Image img;
	VertexArray vertices;
	Texture texture;
};

