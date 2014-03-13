#pragma once
#include <SFML/Graphics/Image.hpp>

using namespace std;

class MapGenerator {
public:
	void Calculate(vector<vector<int>> heightMap, vector<vector<int>> tempMap, vector<vector<int>> rainMap, vector<vector<int>> forestMap);
	sf::Image GetMap();
	MapGenerator();
	~MapGenerator();
	
private:
	vector< vector<int>> points;
	sf::Image map;
};

