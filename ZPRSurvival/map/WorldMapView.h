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
	sf::Vector2f getWorldBounds();
private:
	sf::Image* image;
	sf::Texture* texture;
	sf::Texture* blank;
	sf::Sprite * grass;
	WorldMap* mapa;
};