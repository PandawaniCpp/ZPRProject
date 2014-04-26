#pragma once

#include "SFML/Graphics.hpp"
#include "./../survival/SurvivalObjectView.h"
#include "./../options/GraphicsOptions.h"
#include "WorldMap.h"
#include "PoissonDiskSampling.h"
#include "ChunkView.h"
#include <Vector>
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
	PoissonDiskSampling* poisson;
	std::vector<sf::CircleShape> mapContent;
	std::vector<std::vector<ChunkView*>> chunks;
};