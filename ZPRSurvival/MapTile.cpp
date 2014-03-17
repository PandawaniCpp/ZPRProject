#include "MapTile.h"


MapTile::MapTile() {
	initialized = true;
}

MapTile::MapTile(int size, Texture tile) {
	initialized = false;
	vertices.setPrimitiveType(Quads);
	vertices.resize(4);
	vertices[0].position = sf::Vector2f(0, 0);
	vertices[1].position = sf::Vector2f(size, 0);
	vertices[2].position = sf::Vector2f(size, size);
	vertices[3].position = sf::Vector2f(0, size);
	texture = tile;
	/*if (type == 0) {
		img.create(size, size, sf::Color(0, 18, 25));
	}
	else if (type == 1) {
		img.create(size, size, sf::Color(200, 180, 120));
	}
	else if (type == 2) {
		img.create(size, size, sf::Color(180, 120, 100));
	}
	else if (type == 3) {
		img.create(size, size, sf::Color(100, 120, 50));
	}
	else if (type == 4) {
		img.create(1, 1, sf::Color(50, 100, 30)); 
	}
	else if (type == 5) {
		img.create(1, 1, sf::Color(20, 80, 20)); 
	}
	//else if (points[x][y] == 6) {
	//	map.setPixel(x, y, sf::Color(30, 30, 30)); // ((int)((r / 255.0)*(double)color), (int)((g / 255.0)*(double)color), (int)((b / 255.0)*(double)color)));//This colours the image with the RGB values
	//}
	else if (type == 7) {
		img.create(1, 1, sf::Color(30, 30, 30));
	}
	else {
		img.create(size, size, sf::Color(255, 0, 255));
	}
	
	texture.create(size, size);
	texture.setRepeated(true);
	texture.loadFromImage(img);
	*/
}

MapTile::~MapTile() {
}

void MapTile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = &texture;

	// draw the vertex array
	target.draw(vertices, states);
}

bool MapTile::isInitilaized() {
	return initialized;
}
