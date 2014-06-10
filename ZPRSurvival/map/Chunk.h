#pragma once
#include "../classes/GameObject.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "./../interface/Logger.h"
#include "./../content/scenery/Plant.h"
class Chunk:
	public GameObject {
public:
	Chunk();
	virtual ~Chunk();
	void load();
	void unload();
	void setPositionsVector(const std::vector<sf::Vector2f*> & vect);
	void setObjcets(const sf::Vector2f * wsp);
	std::vector<Plant*> getObjects();
private:
	//teksturyyyyyy
	std::vector<sf::Vector2f*> positions;
	std::vector<Plant*> objects;

};

