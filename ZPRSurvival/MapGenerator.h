#pragma once
#include <SFML/Graphics/Image.hpp>
#include <SFML/Window.hpp>
#include "MidpointDisplacementNoise.h"
#include "PerlinNoise.h"
#include "MapTile.h"
#include <iostream>

using namespace std;

class MapGenerator {
public:
	void Calculate(vector<vector<int>> heightMap, vector<vector<int>> tempMap, vector<vector<int>> rainMap);
	sf::Image GetMap();
	MapGenerator(int w, int h, int s);
	~MapGenerator();
	Vector2f getPosition();
	void draw(sf::RenderWindow* target, int x, int y);
	void move(Vector2f displacement);
private:
	Vector2<float> position;
	vector<vector<int> > points;
	vector<vector<MapTile> > maps;
	Image map;
	Texture tiles[8];
	Image img[8];
	int height, width, scale;
};

