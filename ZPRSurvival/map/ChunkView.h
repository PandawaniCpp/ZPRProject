#pragma once
#include "./../survival/SurvivalObjectView.h"
#include "Chunk.h"
class ChunkView:
	public SurvivalObjectView {
public:
	ChunkView();
	virtual ~ChunkView();
	void draw();
private:
		Chunk* chunk;
};

