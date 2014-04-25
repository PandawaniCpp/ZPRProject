#include "MapTile.h"

MapTile::MapTile(int x, int y, int scale, int zoom, double p, RandomNoise & perlin, int m) {
	tx.create(scale, scale);
	this->x = x;
	this->y = y;
	this->zoom = zoom;
	this->p = p;
	this->scale = scale;
	this->m = m;
	this->perlin = &perlin;
	initialized = false;

	thread t(load, this);
	t.detach();
}

void MapTile::load(MapTile * tile) {
	tile->calculateTexture(tile->x, tile->y, tile->scale, tile->zoom, tile->p, *(tile->perlin), tile->m);
}

void MapTile::calculateTexture(int & x, int & y, int & scale, int & zoom, double & p, RandomNoise & perlin, int & m) {
	//std::lock_guard<std::mutex> guard(mu);

	mu.lock();
	img = perlin.getZoomedTile(x, y, scale, m, zoom, p);
	mu.unlock();

}

void MapTile::setTexture(Texture & texture) {
	Sprite::setTexture(texture);
}

MapTile::~MapTile() {

}

void MapTile::setPosition(float x, float y) {
	if (!initialized) {
		initialized = true;
		tx.loadFromImage(img);

		setTexture(tx);
	}
	Transformable::setPosition(x, y);
	//bckg.setPosition(x + this->getGlobalBounds().width / 2.5f, y + this->getGlobalBounds().height / 2.5f);
}

void MapTile::draw(RenderTarget &target, RenderStates states) const {


	target.draw((Sprite(*this)));
}