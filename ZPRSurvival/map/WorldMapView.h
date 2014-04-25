#pragma once

#include "SFML/Graphics.hpp"
#include "./../survival/SurvivalObjectView.h"
#include "WorldMap.h"

class WorldMapView :
	public SurvivalObjectView {
public:
	WorldMapView();
	~WorldMapView();
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	float t;
private:
	sf::Image* image;
	sf::Texture* texture;
	WorldMap* mapa;
};