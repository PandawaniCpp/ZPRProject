#pragma once

#include <SFML/Graphics/Image.hpp>
class SimpleNoise {
public:
	SimpleNoise(int width, int height, int frequency, int octaves);
	~SimpleNoise();
private:
	//sf::Image GenerateNoise();

	int width_, height_, frequency_, octaves_;
};

