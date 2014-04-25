#pragma once

#include "./../survival/SurvivalObject.h"
#include "PerlinNoise.h"

//default width, height, persistance, zoom and number of octaves
#define WIDTH 150
#define HEIGHT 150
#define PERSISTENCE 0.5
#define ZOOM 500
#define OCTAVES 3

class WorldMap : public SurvivalObject {
public:
	//Construct&Destruct
	WorldMap();
	WorldMap(int seed, double persistence, double zoom, int octaves, int width, int height);
	~WorldMap();

	//Methods
	//getter
	double getMap(int x, int y, int z);
	int getWidth();
	int getHeight();
	sf::Shader & getShader();
	//setter
private:
	void WorldMap::initialize();

	PerlinNoise * perlinNoise;
	sf::Shader * perlinShader;
	sf::Texture * perlinTexture;
	int width;
	int height;
	int octaves;
	double zoom;
	double persistence;
}; 