#pragma once
#include "./../survival/SurvivalObject.h"
#include <vector>
#include <SFML/Graphics.hpp>
class Chunk:
	public SurvivalObject {
public:
	Chunk();
	virtual ~Chunk();
	void load();
	void unload();
	void pushPosition(sf::Vector3i pos);
private:
	//teksturyyyyyy
	std::vector<sf::Vector3i> positions;
	std::vector<SurvivalObject*> objects;

};

