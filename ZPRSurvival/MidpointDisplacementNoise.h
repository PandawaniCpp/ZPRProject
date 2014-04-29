#pragma once
#include <SFML/Graphics/Image.hpp>
#include <ctime>

using namespace sf;
using namespace std;


class MidpointDisplacementNoise {
public:
	MidpointDisplacementNoise();
	MidpointDisplacementNoise(int _offset);
	~MidpointDisplacementNoise();
	Image GetImage();
	Image GetAlphaImage();
	vector<vector<int>> GetVector();
	void AddGradient();
	Image calculateNoiseTile(int width, int height, int randStep, sf::Color & col11, sf::Color & col21, sf::Color & col22, sf::Color  & col12);
	sf::Color mediumColor(sf::Color & col1, sf::Color & col2, sf::Color & col3, sf::Color  & col4);

private:
	void calculateNoiseIsland(int width, int height, int step, bool randomize, bool island, bool invert);
	//sf::Color mediumColor(sf::Color const & col1, sf::Color const & col2, sf::Color const & col3, sf::Color const & col4);
	int CalculateNoise(int x, int y);
	vector< vector<int>> pointsTab_;
	int width_, height_;
	int offset;
};

