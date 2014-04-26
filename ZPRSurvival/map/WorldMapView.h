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
	sf::Image getMapImage();
	void setViewPosition(sf::Vector2f position);
	sf::Vector2f getSpawnPoint();
private:
	sf::Image* image;
	sf::Texture* texture;
	WorldMap* mapa;
};