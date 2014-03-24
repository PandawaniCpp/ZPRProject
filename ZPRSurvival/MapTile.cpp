#include "MapTile.h"


MapTile::MapTile(int size) {
	initialized = true;
	vertices.setPrimitiveType(Quads);
	vertices.resize(4);
	vertices[0].position = sf::Vector2f(0, 0);
	vertices[1].position = sf::Vector2f(100, 0);
	vertices[2].position = sf::Vector2f(100, 100);
	vertices[3].position = sf::Vector2f(0, 100);
}

MapTile::MapTile(Texture &tile) {
	initialized = false;
	texture = tile;
}

MapTile::~MapTile() {
}

void MapTile::setTexture(Texture &tile) {
	initialized = false;
	texture = tile;
}

void MapTile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = &texture;

	// draw the vertex array
	target.draw(vertices, states);
}

bool MapTile::isInitialized () {
	return initialized;
}
