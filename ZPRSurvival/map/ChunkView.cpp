#include "ChunkView.h"


ChunkView::ChunkView() {
	chunk = new Chunk();
}


ChunkView::~ChunkView() {
}


void ChunkView::setObiectArray(const std::vector<sf::Vector2f> & vect) {
	chunk->setPositionsVector(vect);
}