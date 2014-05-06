#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "./../interface/Logger.h"
#include "./WorldMap.h"

#define SIZE_COUNT 3
#define SQRT2 1.414213
#define KMAX 30
#define PI 3.1415
#define DEFAULT_SEED 12483201
#define DISTANCE 500.0
/*
Poisson Disk Sampling class is a class wich computes positions of all objects inluded in game, like trees, stones, buildings and so on.
It also return in vector size of point (trees are bigger than blades of grass)
*/
class PoissonDiskSampling {
public:
	PoissonDiskSampling(float width, float height, WorldMap* map);
	~PoissonDiskSampling();
	/*
	generate location data of objects on map
	function returns vector of:
	-position x
	-position y
	-size of drawen object
	*/
	typedef std::vector<std::vector<std::vector<sf::Vector2f*>>> Positions;
	typedef std::vector <std::vector<bool>> Grid;
	void objectsPosition(WorldMap* map);
	sf::Vector2f* randPoint();
	sf::Vector2i getGrid(const sf::Vector2f* point, const float & size);
	//sf::Vector2f randomActive(std::vector<sf::Vector2f> & activeVector);
	//int checkOccupiedNeighbours(const sf::Vector2i & Grid, const std::vector<sf::Vector2i> & gridVector);
	sf::Vector2f* randNeighbour(const sf::Vector2f* basePoint, const float & distance);
	bool checkNeighbour(const sf::Vector2f* candidate, const float & minRange, const Grid& gridVector, const Positions& positions);
	//void deleteBasePoint(std::vector<sf::Vector2f> & activeVector, const sf::Vector2f & point);
	//void drawlog();
	std::vector<std::vector<std::vector<sf::Vector2f*>>>& getPositions();

private:
	int ilosc;
	Positions positions;
	float mapHeight;
	float mapWidth;
};

