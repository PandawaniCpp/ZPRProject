#pragma once

#include <SFML/Graphics/Image.hpp>


class PerlinNoise {
public:
	PerlinNoise();
	~PerlinNoise();
	sf::Image RenderMap(int w, int h, double zoom, double p, int r, int g, int b);//w and h speak for themselves, zoom wel zoom in and out on it, I usually
private:
	inline double CalculateNoise(double x, double y);
	inline double Interpolate(double a, double b, double x);
	double Noise(double x, double y);
	int offset;
};

