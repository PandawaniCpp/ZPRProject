#include "Chunk.h"


Chunk::Chunk() {


}


Chunk::~Chunk() {
}

void Chunk::load() {

}

void Chunk::unload(){

}

void Chunk::setPositionsVector(const std::vector<sf::Vector2f*> & vect) {
	for (auto& iterator : vect){
		setObjcets(iterator); 
		positions.push_back(iterator);
	}
}

void Chunk::setObjcets(const sf::Vector2f* wsp) {
	Plant* plant = new Plant(*wsp);
	objects.push_back(plant);
}

std::vector<Plant*> Chunk::getObjects() {
	return objects;
}