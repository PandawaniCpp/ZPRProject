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
#define DISTANCE 700.0
/*
Poisson Disk Sampling class is a class wich computes positions of all objects inluded in game, like trees, stones, buildings and so on.
It also return in vector size of point (trees are bigger than blades of grass)
*/
class PoissonDiskSampling {
public:
	
	/*
	default constructor
	*/
	PoissonDiskSampling(float width, float height, WorldMap* map);
	
	/*
	default destructor
	*/
	~PoissonDiskSampling();
	
	// vector of x's and y's of points
	typedef std::vector<std::vector<std::vector<sf::Vector2f*>>> Positions;
	// vector of bools, says if in the grid there is a point
	typedef std::vector <std::vector<bool>> Grid;
	
	/*
	generate location data of objects on map
	function returns vector of:
	-position x
	-position y
	-size of drawen object
	*/
	void objectsPosition(WorldMap* map);
	
	/*
	Randomize x and y of new point
	returns pointer to Vector [x,y]
	*/
	sf::Vector2f* randPoint();
	
	/*
	calculates the grid in which point is located
	params
	point - x,y of point
	size - size of one grid
	returns vector [x,y] of grid
	*/
	sf::Vector2i getGrid(const sf::Vector2f* point, const float & size);
	
	/*
	Function randomizes neighbour for point.
	params - 
	vector [x,y] of points,
	min distance beetween points
	*/
	sf::Vector2f* randNeighbour(const sf::Vector2f* basePoint, const float & distance);
	bool checkNeighbour(const sf::Vector2f* candidate, const float & minRange, const Grid& gridVector, const Positions& positions);
	
	/*
	returns vector of point posistions
	*/
	std::vector<std::vector<std::vector<sf::Vector2f*>>>& getPositions();

private:
	//counter how many points have been randomized
	int ilosc;
	// vector of positions
	Positions positions;
	//height of the map
	float mapHeight;
	//width of the map
	float mapWidth;
};

