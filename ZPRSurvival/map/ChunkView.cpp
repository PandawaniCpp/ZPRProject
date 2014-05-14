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
	std::vector<sf::CircleShape*> obj = chunk->getObjects();
	for (auto& iterator : obj) {
		target.draw(*iterator);
	}




}