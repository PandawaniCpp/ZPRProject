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
		positions.push_back(iterator);
	}
}