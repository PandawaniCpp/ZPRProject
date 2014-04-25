#pragma once

#include <SFML/Graphics/Image.hpp>
#include <cmath>
#include <ctime>

using namespace std;

class RandomNoise {
public:
	RandomNoise();
	RandomNoise(int const & w, int const & h, int const & z, double const & p, int const & octaves, int const & offset, bool bIsland);
	~RandomNoise();
	sf::Image getZoomedTile(int & x, int & y, int & size, int & moisture, int & zoom, double & p);
	sf::Image & getImage();
	vector<vector<int>> getVector();
	void calculateIsland(bool bIsland);

private:
	sf::Color heury(int h, int m);
	sf::Image renderNoise(int w, int h, float zoom, float p, int r, int g, int b);
	inline double calculateNoise(double x, double y);
	inline double interpolate(double a, double b, double x);
	double noise(double x, double y);
	int offset;
	sf::Image noiseImg;
	sf::Image heur;
	vector<vector<int>> mapVec;
	int width, height;
	int zoom, octaves;
	double p;
};