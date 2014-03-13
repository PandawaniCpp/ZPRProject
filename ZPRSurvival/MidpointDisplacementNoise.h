#pragma once
#include <SFML/Graphics/Image.hpp>
#include <ctime>

using namespace sf;
using namespace std;


class MidpointDisplacementNoise {
public:
	MidpointDisplacementNoise(int width, int height, int step, bool randomize, bool island, bool invert);
	~MidpointDisplacementNoise();
	Image GetImage();
	vector<vector<int>> GetVector();
	void AddGradient();
private:
	int CalculateNoise(int x, int y);
	vector< vector<int>> pointsTab_;
	int width_, height_;
	int offset;
};

