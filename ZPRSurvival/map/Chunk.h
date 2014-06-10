#pragma once
#include "../classes/GameObject.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "./../interface/Logger.h"
#include "./../content/scenery/Plant.h"

/*
	chunk is a sector of the map, on withc are placed plats
*/
class Chunk:
	public GameObject {
public:
	/*
	default constructor
	*/
	Chunk();

	/*
	default destructor
	*/
	virtual ~Chunk();
	
	/*
	set positions of the points
	*/
	void setPositionsVector(const std::vector<sf::Vector2f*> & vect);

	/*
	sets vector of the plants
	*/
	void setObjcets(const sf::Vector2f * wsp);
	
	/*
	returns vector of plants
	*/
	std::vector<Plant*> getObjects();

private:

	// vector of positions
	std::vector<sf::Vector2f*> positions;
	// vector of plants
	std::vector<Plant*> objects;

};

