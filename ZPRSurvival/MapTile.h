#pragma once
#include "SFML/Graphics.hpp"
#include "RandomNoise.h"
#include <thread>
#include <mutex>

using namespace sf;

class MapTile : public Sprite {
public:
	MapTile(int x, int y, int scale, int zoom, double p, RandomNoise & perlin, int m);
	void calculateTexture(int & x, int & y, int & scale, int & zoom, double & p, RandomNoise & perlin, int & m);
	~MapTile();
	void setTexture(Texture & texture);
	void draw(RenderTarget &target, RenderStates states) const;
	static void load(MapTile * tile);
	void initialize();
	void setPosition(float x, float y);
	//virtual void draw(RenderTarget& target) const;
private:
	int x, y,
		zoom, scale, m;
	double p;
	bool initialized;
	Mutex mu;
	RandomNoise * perlin;
	sf::VertexArray vertices;
	Sprite bckg;
	Texture tx;	
	Image img;
	
};

