#include "WorldMap.h"


WorldMap::WorldMap() {
	zoom = ZOOM;
	persistence = PERSISTENCE;
	octaves = OCTAVES;
	width = WIDTH;
	height = HEIGHT;
	perlinNoise = new PerlinNoise();
	perlinShader = new sf::Shader();
	perlinTexture = new sf::Texture();
	initialize();
}

WorldMap::WorldMap(int seed, double persistence, double zoom, int octaves, int width, int height) {
	this->zoom = zoom;
	this->persistence = persistence;
	this->octaves = octaves;
	this->width = width;
	this->height = height;
	perlinNoise = new PerlinNoise(seed);
	perlinShader = new sf::Shader();
	perlinTexture = new sf::Texture();
	initialize();
}

void WorldMap::initialize() {
	perlinShader->loadFromFile("./shaders/PerlinShader.glsl", sf::Shader::Fragment);
	perlinTexture->create(16, 16);
	perlinTexture->loadFromImage(perlinNoise->getPermutationImage());
	perlinNoise->getPermutationImage().saveToFile("./perlin.png");
	perlinShader->setParameter("permutationVector", *perlinTexture);
}

WorldMap::~WorldMap() {
	delete perlinNoise;
	delete perlinShader;
	delete perlinTexture;
}

double WorldMap::getMap(int x, int y, int z) {
	double t = 0.0;
	double amplitude = 1.0;
	double frequency = 1;
	for (int i = 0; i < octaves; i++) {
		t += perlinNoise->noise(x*frequency / zoom, y*frequency / zoom, z/1000.0)*amplitude;
		amplitude *= persistence;
		frequency *= 2;
	}

	return t;
}

int WorldMap::getWidth() {
	return width;
}

int WorldMap::getHeight() {
	return height;
}

sf::Shader & WorldMap::getShader() {
	return *perlinShader;
}