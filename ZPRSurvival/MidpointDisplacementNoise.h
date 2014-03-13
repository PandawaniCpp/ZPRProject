#pragma once
#include <SFML/Graphics/Image.hpp>

using namespace sf;
using namespace std;


class MidpointDisplacementNoise {
public:
	MidpointDisplacementNoise(int width, int height, int step);
	~MidpointDisplacementNoise();
	Image GetImage();
private:
	vector< vector<int>> pointsTab_;
	int width_, height_;
};

