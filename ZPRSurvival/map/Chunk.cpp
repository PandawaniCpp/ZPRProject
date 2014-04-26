#include "Chunk.h"


Chunk::Chunk() {


}


Chunk::~Chunk() {
}

void Chunk::load() {

}

void Chunk::unload(){

}

void Chunk::pushPosition(sf::Vector3i pos){
	positions.push_back(pos);
}