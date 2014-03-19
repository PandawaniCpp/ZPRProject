#include "MapGenerator.h"

using namespace std;

MapGenerator::MapGenerator(int w, int h, int s) {
	scale = s;
	height = h;
	width = w;
	PerlinNoise heightNoise(w, h, 300, 0.5, 7, true);
	PerlinNoise rainNoise(w, h, 200, 0.5, 5, false);
	position = Vector2f(-w*scale / 2, -h*scale / 2);

	this->Calculate(heightNoise.GetVector(), rainNoise.GetVector());

	img[0].create(scale, scale, sf::Color(0, 18, 25));
	img[1].create(scale, scale, sf::Color(200, 180, 120));
	img[2].create(scale, scale, sf::Color(180, 120, 100));
	img[3].create(scale, scale, sf::Color(100, 120, 50));
	img[4].create(scale, scale, sf::Color(50, 100, 30));
	img[5].create(scale, scale, sf::Color(20, 80, 20));
	img[6].create(scale, scale, sf::Color(50, 50, 50));
	img[7].create(scale, scale, sf::Color(30, 30, 30));

	for (int i = 0; i < 8; i++) {
		tiles[i] = new Texture();
		tiles[i]->create(scale, scale);
		//tiles[i].setRepeated(true);
		tiles[i]->loadFromImage(img[i]);
	}


}

MapGenerator::~MapGenerator() {
}

void MapGenerator::Calculate(vector<vector<int>> const & heightMap, vector<vector<int>> const & rainMap) {
	int iter = 4;
	int w = width;
	int h = height;

	map.create(w, h, sf::Color::Black);

	points.resize(w, vector<int>(h, 0));
	maps.resize(w, vector<MapTile>(h, MapTile(scale)));

	for (int y = 0; y < w; y++) {//Loops to loop trough all the pixels
		for (int x = 0; x < h; x++) {

			int height = heightMap[x][y];
			int rain = rainMap[x][y];

			if (height <= 75) {
				points[x][y] = 0; // water
			}
			else if (height <= 85) { //sand
				points[x][y] = 1;
			}
			else if (height <= 115) { //lower terrain
				if (rain <= 40) {
					points[x][y] = 2; //desert
				}
				else if (rain <= 65) {
					points[x][y] = 3; //grassland
				}
				else {
					points[x][y] = 4; //tropical forest
				}
			}
			else if (height <= 140) { //
				if (rain <= 50) {
					points[x][y] = 2; //desert
				}
				else if (rain <= 75) {
					points[x][y] = 3; //grassland
				}
				else {
					points[x][y] = 5; // forest
				}
			}
			//	else if (height <= 160) {
			//		points[x][y] = 6; //mountains
			//	}
			else {
				points[x][y] = 7; //mountains
			}
		}
	}

}

void MapGenerator::move(Vector2f &displacement) {
	position += Vector2<float>(displacement.x, displacement.y);
}

Vector2f MapGenerator::getPosition() {
	return position;
}

void MapGenerator::loadMap(MapTile & map, Texture & texture) {
	map.setTexture(texture);
}

void MapGenerator::draw(sf::RenderWindow* target) {
	int startX = - position.x / scale;
	int startY = - position.y / scale;
	int endX = 1 + 1200/scale - position.x / scale;
	int endY = 1 + 700/scale - position.y / scale;

	if (startX < 0) {
		startX = 0;
	}

	if (startY < 0) {
		startY = 0;
	}
	if (endX >= width) {
		endX = width;
	}
	if (endY>= height) {
		endY = height;
	}
	vector<thread> threads;
	for (int i = startX; i < endX; i++) {
		for (int j = startY; j < endY; j++) {

			//if (maps[i][j].isInitilaized()) {
			if (maps[i][j].isInitilaized() == true) {
				maps[i][j].setTexture(*tiles[points[i][j]]);
			}
				//maps[i][j].setTexture(tiles[points[i][j]]);
				//loadMap(maps[i][j], tiles[points[i][j]]);
				//threads.push_back( thread(loadMap, maps[i][j], tiles[points[i][j]]));
				//threads[(i - startX)*(endX - startX) + (j - startY)].join();
			
			maps[i][j].setPosition(i*scale + position.x, j*scale + position.y);
			target->draw(maps[i][j]);
		}
	}
}