#pragma once

#include "SFML/Graphics.hpp"
#include "./../survival/SurvivalObjectView.h"
#include "./../options/GraphicsOptions.h"
#include "WorldMap.h"
#include "ChunkView.h"
#include "./PoissonDiskSampling.h"

class WorldMapView :
	public SurvivalObjectView {
public:
	WorldMapView();
	WorldMapView(int seed, double persistence, double zoom, int octaves, int width, int height);
	~WorldMapView();
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void update();
	float t;
	sf::Image getMapImage();
	void setViewPosition(sf::Vector2f position);
	sf::Vector2f getSpawnPoint();
	sf::Vector2f getViewPosition();
	sf::Vector2f getWorldBounds();
	PoissonDiskSampling * getPoisson ();

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
	typedef std::vector < std::vector<ChunkView*>> ChunkArray;
	//typedef std::vector <std::vector<std::vector<sf::Vector2f>>> ChunkObjectsArray;
	sf::Vector2i last;
	PoissonDiskSampling* poisson;
	ChunkArray chunkArray;
};