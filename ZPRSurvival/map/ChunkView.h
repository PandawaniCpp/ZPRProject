#pragma once
#include "../classes/GameObject.h"
#include "Chunk.h"
#include "./../interface/Logger.h"

/*
Chunk view is actually a Controller of the chunk.
it commands chunk to draw or return objects
*/
class ChunkView:
	public GameObject {
public:
	
	/*
	default constructor
	*/
	ChunkView();
	
	/*
	default destructor
	*/
	virtual ~ChunkView();

	/*
	calls draw function on chunk
	*/
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	
	/*
	sets vector of positions of the objects
	*/
	void setObiectArray(const std::vector<sf::Vector2f*> & vect);

private:
		//pointer to chunk
		Chunk* chunk;
};

