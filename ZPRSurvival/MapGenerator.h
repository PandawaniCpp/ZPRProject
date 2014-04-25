#pragma once
#include <SFML/Graphics/Image.hpp>
#include <SFML/Window.hpp>
#include "MidpointDisplacementNoise.h"
#include "RandomNoise.h"
#include "MapTile.h"
#include <thread>
#include <iostream>

using namespace std;

class MapGenerator {
public:
	void Calculate(vector<vector<int>> const & heightMap, vector<vector<int>> const & rainMap);
	sf::Image GetMap();
	MapGenerator(int w, int h, int s);
	~MapGenerator();
	Vector2f getPosition();
	void draw(sf::RenderWindow * target);
	void move(Vector2f & displacement);
	void loadMap(int startX, int startY, int endX, int endY);
	sf::Image randomNoise(int width, int height);
private:
	//thread loader;
	RandomNoise * heightNoise;
	RandomNoise * rainNoise;
	Vector2<float> position;
	Vector2i currentTile, lastTile;
	vector<vector<int> > points;
	vector<vector<int> > rain;
	vector<vector<int> > heights;
	vector<vector< MapTile *> > maps;
	Image map;
	Image heur;
	Texture * tiles[16];
	Texture white;
	RandomNoise * perlin[16];
	Image img[16];
	Color col[8];
	int height, width, scale;
};

