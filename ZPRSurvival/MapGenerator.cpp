#include "MapGenerator.h"


MapGenerator::MapGenerator(int w, int h, int s) {
	scale = s;
	height = h;
	width = w;
	PerlinNoise heightNoise(w, h, 300, 0.5, 7, true);
	MidpointDisplacementNoise tempNoise(w, h, w / 2, true, true, true);
	PerlinNoise rainNoise(w, h, 200, 0.5, 5, false);
	position = Vector2f(-32 * 2048.0f, -32 * 2048.0f);
	tempNoise.AddGradient();
	this->Calculate(heightNoise.GetVector(), tempNoise.GetVector(), rainNoise.GetVector());

	img[0].create(scale, scale, sf::Color(0, 18, 25));
	img[1].create(scale, scale, sf::Color(200, 180, 120));
	img[2].create(scale, scale, sf::Color(180, 120, 100));
	img[3].create(scale, scale, sf::Color(100, 120, 50));
	img[4].create(scale, scale, sf::Color(50, 100, 30));
	img[5].create(scale, scale, sf::Color(20, 80, 20));
	img[6].create(scale, scale, sf::Color(50, 50, 50));
	img[7].create(scale, scale, sf::Color(30, 30, 30));

	for (int i = 0; i < 8; i++) {
		tiles[i].create(scale, scale);
		tiles[i].setRepeated(true);
		tiles[i].loadFromImage(img[i]);
	}


}

MapGenerator::~MapGenerator() {
}

void MapGenerator::Calculate(vector<vector<int>> heightMap, vector<vector<int>> tempMap, vector<vector<int>> rainMap) {
	int iter = 4;
	int w = width;
	int h = height;

	map.create(h, w, sf::Color::Black);

	points.resize(h, vector<int>(w, 0));
	maps.resize(h, vector<MapTile>(w, MapTile()));

	for (int y = 0; y < w; y++) {//Loops to loop trough all the pixels
		for (int x = 0; x < h; x++) {

			int height = heightMap[x][y];
			int temperature = tempMap[x][y];
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

void MapGenerator::move(Vector2f displacement) {
	position += Vector2<float>(displacement.x, displacement.y);
}

Vector2f MapGenerator::getPosition() {
	return position;
}

void MapGenerator::draw(sf::RenderWindow* target, int x, int y) {

	//target->draw(MapTile(0,128));

	int start_x = -position.x / scale - 2;
	int start_y = -position.y / scale - 2;

	if (start_x < 0) {
		start_x = 0;
	}
	else if (start_x + 15 >= width) {
		start_x = width - 1;
	}

	if (start_y < 0) {
		start_y = 0;
	}
	else if (start_y + 15 >= height) {
		start_y = height - 1;
	}

	for (int i = start_x; i < start_x + 24; i++) {
		for (int j = start_y; j < start_y + 20; j++) {
			if (maps[i][j].isInitilaized()) {
				maps[i][j] = MapTile(scale, tiles[points[i][j]]);
			}
			maps[i][j].setPosition(i*scale + position.x, j*scale + position.y);
			if (maps[i][j].getPosition().x >= -64 &&
				maps[i][j].getPosition().y >= -64 &&
				maps[i][j].getPosition().x <= 1200 &&
				maps[i][j].getPosition().y <= 700) {
				target->draw(maps[i][j]);
			}
		}
	}
}