#include "Chunk.h"


Chunk::Chunk() {


}


Chunk::~Chunk() {
}

void Chunk::load() {

}

void Chunk::unload(){

}

void Chunk::setPositionsVector(const std::vector<sf::Vector2f> & vect) {
	for (auto& iterator : vect){
		setObjcets(iterator); 
		positions.push_back(iterator);
	}
}

void Chunk::setObjcets(const sf::Vector2f& wsp) {
	sf::CircleShape* circle = new sf::CircleShape();
	circle->setPosition(wsp.x, wsp.y);
	circle->setFillColor(sf::Color::Red);
	circle->setRadius(20);
	objects.push_back(circle);
}

std::vector<sf::CircleShape*> Chunk::getObjects() {
	return objects;
}