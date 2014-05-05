#include "WorldMap.h"


WorldMap::WorldMap() {
	zoom = ZOOM;
	persistence = PERSISTENCE;
	octaves = OCTAVES;
	width = WIDTH;
	height = HEIGHT;
	viewPosition = sf::Vector2f(0.0f, 0.0f);
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
	viewPosition = sf::Vector2f(0.0f, 0.0f);
	perlinNoise = new PerlinNoise(seed);
	perlinShader = new sf::Shader();
	perlinTexture = new sf::Texture();
	initialize();
}

void WorldMap::initialize() {
	perlinShader->loadFromFile("./shaders/MapShader.vert", "./shaders/MapShader.frag");
	//perlinShader->loadFromFile("./shaders/TestShader.vert", "./shaders/TestShader.frag");	
	perlinTexture->create(16, 16);
	perlinTexture->loadFromImage(perlinNoise->getPermutationImage());
	perlinNoise->getPermutationImage().saveToFile("./perlin.png");
	perlinShader->setParameter("permutationVector", *perlinTexture);
	perlinShader->setParameter("resolutionX", GraphicsOptions::videoMode.width);
	perlinShader->setParameter("resolutionY", GraphicsOptions::videoMode.height);
	perlinShader->setParameter("offsetX", 0.0f);
	perlinShader->setParameter("offsetY", 0.0f);
	perlinShader->setParameter("height", height);
	perlinShader->setParameter("width", width);
	perlinShader->setParameter("zoom", zoom);
	perlinShader->setParameter("persistence", persistence);
	perlinShader->setParameter("octaves", octaves);
}

WorldMap::~WorldMap() {
	delete perlinNoise;
	delete perlinShader;
	delete perlinTexture;
}

double WorldMap::getMap(int x, int y, int z) {
	double t = 1.0;
	double amplitude = 1.0;
	double frequency = 1;
	
	if (x > 0.6*width) {
		t -= 2.0*(25.0 / 4.0) * pow((x - width*0.6), 2) / pow(width, 2);
	}
	else if (x < 0.4f*width) {
		t -= 2.0*(25.0 / 4.0) * pow((width*0.4 - x), 2) / pow(width, 2);
	}
	if (y > 0.6*height) {
		t -= 2.0*(25.0 / 4.0) * pow((y - height*0.6), 2) / pow(height, 2);
	}
	else if (y < 0.4*height) {
		t -= 2.0*(25.0 / 4.0) * pow((height*0.4 - y), 2) / pow(height, 2);
	}

	for (int i = 0; i < octaves; i++) {
		t += perlinNoise->noise(x*frequency / zoom, y*frequency / zoom, z / 1000.0)*amplitude;
		amplitude *= persistence;
		frequency *= 2.5;
	}

	if (t < -1.0) {
		t = -1.0;
	}

	if (t >= 2.0) {
		t = 2.0;
	}

	return 127.5*(t+1);
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

void WorldMap::setViewPosition(sf::Vector2f position) {
	viewPosition = position;
}

sf::Vector2f WorldMap::getViewPosition() {
	return viewPosition;
}