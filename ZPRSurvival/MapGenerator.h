#pragma once
#include <SFML/Graphics/Image.hpp>
#include "MidpointDisplacementNoise.h"

using namespace std;

class MapGenerator {
public:
	void Calculate(vector<vector<int>> heightMap, vector<vector<int>> tempMap, vector<vector<int>> rainMap, vector<vector<int>> forestMap);
	sf::Image GetMap();
	MapGenerator(int w, int h);
	~MapGenerator();
	
private:
	vector< vector<int>> points;
	sf::Image map;
};

