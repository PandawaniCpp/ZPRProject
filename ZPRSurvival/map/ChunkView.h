#pragma once
#include "./../survival/SurvivalObjectView.h"
#include "Chunk.h"
class ChunkView:
	public SurvivalObjectView {
public:
	ChunkView();
	virtual ~ChunkView();
	void draw();
	void setObiectArray(const std::vector<sf::Vector2f> & vect);
private:
		Chunk* chunk;
};

