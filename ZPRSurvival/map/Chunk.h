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
	void setPositionsVector(const std::vector<sf::Vector2f> & vect);
	void setObjcets(const sf::Vector2f& wsp);
	std::vector<sf::CircleShape*> getObjects();
private:
	//teksturyyyyyy
	std::vector<sf::Vector2f> positions;
	std::vector<sf::CircleShape*> objects;

};

