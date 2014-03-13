#pragma once
#include <SFML/Graphics/Image.hpp>

using namespace std;

class MapGenerator {
public:
	void Calculate(sf::Image heightMap);
	sf::Image GetMap();
	MapGenerator();
	~MapGenerator();
	
private:
	vector< vector<int>> points;
	sf::Image map;
};

