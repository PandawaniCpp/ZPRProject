#pragma once
#include "./../survival/SurvivalObjectView.h"
#include "Chunk.h"
#include "./../interface/Logger.h"
class ChunkView:
	public SurvivalObjectView {
public:
	ChunkView();
	virtual ~ChunkView();
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void setObiectArray(const std::vector<sf::Vector2f> & vect);
private:
		Chunk* chunk;
};

