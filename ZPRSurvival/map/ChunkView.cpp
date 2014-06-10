#include "ChunkView.h"


ChunkView::ChunkView() {
	chunk = new Chunk();
}


ChunkView::~ChunkView() {
}


void ChunkView::setObiectArray(const std::vector<sf::Vector2f*> & vect) {
	chunk->setPositionsVector(vect);
}

void ChunkView::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	std::vector<Plant*> obj = chunk->getObjects();
	for (auto& iterator : obj) {
		target.draw(*iterator, states);
		target.draw(iterator->getFoodAmountBar(), states);
	}
}

void ChunkView::update() {
	std::vector<Plant*> obj = chunk->getObjects();
	for (auto& iterator : obj) {
		iterator->update();
	}
}

void ChunkView::decreaseFood(const unsigned long long id) {
	std::vector<Plant*> obj = chunk->getObjects();
	for (auto& iterator : obj) {
		if (iterator->getEntityInfo().id == id)
			iterator->isEaten();
	}

}