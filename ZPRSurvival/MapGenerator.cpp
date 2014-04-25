#include "MapGenerator.h"

using namespace std;

MapGenerator::MapGenerator(int w, int h, int s) {
	scale = s;
	height = h;
	width = w;
	srand(time(NULL));
	heightNoise = new RandomNoise(w, h, 300, 0.5, 10, rand(), true);
	rainNoise = new RandomNoise(w, h, 800, 0.5, 3, rand(), false);
	//heightNoise->calculateIsland(true);
	//rainNoise->calculateIsland(false);
	rain = rainNoise->getVector();
	heights = heightNoise->getVector();
	position = Vector2f(-w*scale / 5, -h*scale / 5);
	heur.loadFromFile("./resources/map/Map.png");

	heightNoise->getImage().saveToFile("h.png");
	rainNoise->getImage().saveToFile("r.png");

	currentTile = lastTile = Vector2i(w / 2, h / 2);

	this->Calculate(heightNoise->getVector(), rain);

	col[0] = sf::Color(0, 18, 25);
	col[1] = sf::Color(200, 180, 120);
	col[2] = sf::Color(180, 120, 100);
	col[3] = sf::Color(100, 120, 50);
	col[4] = sf::Color(20, 80, 20);
	col[5] = sf::Color(50, 100, 30);
	col[6] = sf::Color(50, 50, 50);
	col[7] = sf::Color(30, 30, 30);


	int zoom = 15;
	double p = 0.6;
	int octaves = 6;
	bool island = false;




	for (int i = 0; i < 16; i++) {
		tiles[i] = new Texture();
		tiles[i]->create(scale, scale);
		//tiles[i].setRepeated(true);
		tiles[i]->loadFromImage(img[i]);
	}


	Image iWhite;
	iWhite.create(scale, scale, sf::Color::White);
	white.loadFromImage(iWhite);
	white.setRepeated(false);

}

MapGenerator::~MapGenerator() {
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			if (maps[i][j]) {
				delete maps[i][j];
				maps[i][j] = NULL;
			}
		}
	}
}

void MapGenerator::Calculate(vector<vector<int>> const & heightMap, vector<vector<int>> const & rainMap) {
	int iter = 1;
	int w = width;
	int h = height;

	map.create(w, h, sf::Color::Black);

	points.resize(w, vector<int>(h, 0));
	maps.resize(w, vector<MapTile *>(h, NULL));

	for (int y = 0; y < w; ++y) {//Loops to loop trough all the pixels
		for (int x = 0; x < h; ++x) {

			int height = heightMap[x][y];
			int rain = 100;// rainMap[x][y];

			if (height <= 80) {
				points[x][y] = 0; // water
			}
			else if (height <= 90) { //sand
				points[x][y] = 1;
			}
			else if (height <= 160) { //lower terrain
				if (rain <= 80) {
					points[x][y] = 2; //desert
				}
				else if (rain <= 130) {
					points[x][y] = 3; //grassland
				}
				else {
					points[x][y] = 4; //tropical forest
				}
			}
			else if (height <= 200) { //
				if (rain <= 100) {
					points[x][y] = 2; //desert
				}
				else if (rain <= 140) {
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

void MapGenerator::loadMap(int startX, int  startY, int  endX, int endY) {
	int startXX = startX;
	int startYY = startY;
	int endXX = endX;
	int endYY = endY;
	int sx, ex, sy, ey;
	sx = ex = sy = ey = 3;

	while (startXX > 0 && sx > 0) {
		--startXX;
		--sx;
	}

	while (endXX < width - 1 && ex > 0) {
		++endXX;
		--ex;
	}

	while (startYY > 0 && sy > 0) {
		--startYY;
		--sy;
	}

	while (endYY < height - 1 && ey>0) {
		++endYY;
		--ey;
	}

	for (int i = startXX; i < endXX; ++i) {
		for (int j = startYY; j < endYY; ++j) {

			if (i < startXX || j < startYY || i > endXX || j > endYY) {
				if (maps[i][j]) {

					delete maps[i][j];
					maps[i][j] = NULL;
				}
			}
			else {

				if (!(maps[i][j])) {
					maps[i][j] = new MapTile(i, j, scale, 30000, 0.3, *heightNoise, 100);// col[points[i][j]], col[points[i][j + 1]], col[points[i + 1][j + 1]], col[points[i + 1][j]]);
				}
			}
		}
	}
}

void MapGenerator::draw(sf::RenderWindow* target) {
	int startX = -position.x / scale - 2;
	int startY = -position.y / scale - 2;
	int endX = 1 + 1200 / scale - position.x / scale;
	int endY = 1 + 700 / scale - position.y / scale;

	if (startX < 0) {
		startX = 0;
	}

	if (startY < 0) {
		startY = 0;
	}
	if (endX >= width) {
		endX = width - 1;
	}
	if (endY >= height) {
		endY = height - 1;
	}

	currentTile = Vector2i(-position.x / scale + 600 / scale, -position.y / scale + 350 / scale);

	if (currentTile != lastTile) {
		lastTile = currentTile;
		loadMap(startX, startY, endX, endY);
	}



	vector<thread> threads;
	for (int i = startX; i < endX; ++i) {
		for (int j = startY; j < endY; ++j) {
			if (maps[i][j]) {
				maps[i][j]->setPosition(i*scale + position.x, j*scale + position.y);
				//maps[i][j]->initialize();
				target->draw(*maps[i][j]);
			}
		}
	}
}

sf::Image MapGenerator::GetMap() {
	map.create(width, height, sf::Color::Black);

	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			map.setPixel(i, j, heur.getPixel(rain[i][j], heights[i][j]));
		}
	}

	return map;
}

sf::Image MapGenerator::randomNoise(int w, int h) {
	Image image;
	image.create(w, h, sf::Color::Black);



	for (int i = 0; i < w; ++i) {
		for (int j = 0; j < h; ++j) {

			float distanceFromCenter = 1.0f;

			if (i > 0.66f*w) {
				distanceFromCenter -= (2.0f) * (i - w*0.5f) / w;
			}
			if (j > 0.66f*h) {
				distanceFromCenter -= (2.0f) * (j - h*0.5f) / h;
			}
			if (i < 0.33f*w) {
				distanceFromCenter -= (2.0f) * (w*0.5f - i) / w;
			}
			if (j < 0.33f*h) {
				distanceFromCenter -= (2.0f) * (h*0.5f - j) / h;
			}

			if (distanceFromCenter < 0.0f) {
				distanceFromCenter = 0.0f;
			}


			int c = rand() % 180 + 75;
			c *= distanceFromCenter;
			image.setPixel(i, j, sf::Color(c, c, c));
		}
	}

	return image;
}