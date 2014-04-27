#pragma once

#include "SFML/Graphics.hpp"
#include "./../survival/SurvivalObjectView.h"
#include "./../options/GraphicsOptions.h"
#include "WorldMap.h"

class WorldMapView :
	public SurvivalObjectView {
public:
	WorldMapView();
	WorldMapView(int seed, double persistence, double zoom, int octaves, int width, int height);
	~WorldMapView();
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	float t;
	sf::Image getMapImage();
	void setViewPosition(sf::Vector2f position);
	sf::Vector2f getSpawnPoint();
	sf::Vector2f getViewPosition();
	sf::Vector2f getWorldBounds();
	float getMapa(int x, int y);
private:
	void initialize();

	sf::Image* waterImage;
	sf::Texture* waterTexture;
	sf::Sprite * waterSprite;
	sf::Image* sandImage;
	sf::Texture* sandTexture;
	sf::Sprite * sandSprite;
	sf::Image* grassImage;
	sf::Texture* grassTexture;
	sf::Sprite * grassSprite;

	WorldMap* mapa;
};