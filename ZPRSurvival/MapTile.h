#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;

class MapTile :	public Drawable, public Transformable {
public:
	MapTile(int size);
	MapTile(Texture &tile);
	~MapTile();
	void setTexture(Texture &tile);
	bool isInitilaized();
	virtual void draw(RenderTarget& target, RenderStates states) const;
private:
	bool initialized;
	Image img;
	VertexArray vertices;
	Texture texture;
};

