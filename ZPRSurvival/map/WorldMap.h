#pragma once

#include <SFML/Graphics.hpp>
#include "./../survival/SurvivalObject.h"
#include "PerlinNoise.h"
#include "./../options/GraphicsOptions.h"

//default width, height, persistance, zoom and number of octaves
#define WIDTH 2000
#define HEIGHT 2000
#define PERSISTENCE 0.5
#define ZOOM 1600
#define OCTAVES 9

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
	sf::Vector2f getViewPosition();
	//setter
	void setViewPosition(sf::Vector2f position);
private:
	void initialize();

	sf::Vector2f viewPosition;
	PerlinNoise * perlinNoise;
	sf::Shader * perlinShader;
	sf::Texture * perlinTexture;
	int width;
	int height;
	int octaves;
	double zoom;
	double persistence;
}; 