#pragma once

#include <SFML/Graphics/Image.hpp>
#include <cmath>
#include <ctime>

using namespace std;

class PerlinNoise {
public:
	PerlinNoise(int w, int h, double zoom, double p, int r, int g, int b, int octaves);
	~PerlinNoise();
	sf::Image RenderTerrainMap(int xS, int yS, int size);
	sf::Image RenderTemperatureMap(int w, int h, double zoom, double p, int r, int g, int b);
	sf::Image GetImage();
	void AddGradient();
private:
	sf::Image RenderNoise(int w, int h, double zoom, double p, int r, int g, int b);
	inline double CalculateNoise(double x, double y);
	inline double Interpolate(double a, double b, double x);
	double Noise(double x, double y);
	int offset;
	sf::Image noise;
	vector<vector<int>> mapVec;
};