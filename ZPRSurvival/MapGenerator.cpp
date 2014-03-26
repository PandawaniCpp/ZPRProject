#include "MapGenerator.h"

using namespace std;

MapGenerator::MapGenerator(int w, int h, int s) {
	scale = s;
	height = h;
	width = w;
	PerlinNoise heightNoise(w, h, 300, 0.5, 7, true);
	PerlinNoise rainNoise(w, h, 400, 0.6, 4, false);
	position = Vector2f(-w*scale / 2, -h*scale / 2);

	//	heightNoise.GetImage().saveToFile("height1.png");
	rainNoise.GetImage().saveToFile("rain.png");

	currentTile = lastTile = Vector2i(w / 2, h / 2);

	this->Calculate(heightNoise.GetVector(), rainNoise.GetVector());

	col[0] = sf::Color(0, 18, 25);
	col[1] = sf::Color(200, 180, 120);
	col[2] = sf::Color(180, 120, 100);
	col[3] = sf::Color(100, 120, 50);
	col[4] = sf::Color(20, 80, 20);
	col[5] = sf::Color(50, 100, 30);
	col[6] = sf::Color(50, 50, 50);
	col[7] = sf::Color(30, 30, 30);

	scale *= 5;

	int zoom =	18;
	double p =	0.95;
	int octaves = 7;

	perlin[0] = new PerlinNoise(scale, scale, zoom, p, octaves, true);
	perlin[1] = new PerlinNoise(scale, scale, zoom, p, octaves, true);
	perlin[2] = new PerlinNoise(scale, scale, zoom, p, octaves, true);
	perlin[3] = new PerlinNoise(scale, scale, zoom, p, octaves, true);
	perlin[4] = new PerlinNoise(scale, scale, zoom, p, octaves, true);
	perlin[5] = new PerlinNoise(scale, scale, zoom, p, octaves, true);
	perlin[6] = new PerlinNoise(scale, scale, zoom, p, octaves, true);
	perlin[7] = new PerlinNoise(scale, scale, zoom, p, octaves, true);
	perlin[8] = new PerlinNoise(scale, scale, zoom, p, octaves, true);
	perlin[9] = new PerlinNoise(scale, scale, zoom, p, octaves, true);
	perlin[10] = new PerlinNoise(scale, scale, zoom, p, octaves, true);
	perlin[11] = new PerlinNoise(scale, scale, zoom, p, octaves, true);
	perlin[12] = new PerlinNoise(scale, scale, zoom, p, octaves, true);
	perlin[13] = new PerlinNoise(scale, scale, zoom, p, octaves, true);
	perlin[14] = new PerlinNoise(scale, scale, zoom, p, octaves, true);
	perlin[15] = new PerlinNoise(scale, scale, zoom, p, octaves, true);

	scale /= 5;

	for (int i = 0; i < 16; i++) {
		img[i] = perlin[i]->GetImage();
		tiles[i] = new Texture();
		tiles[i]->create(scale * 5, scale * 5);
		//tiles[i].setRepeated(true);
		tiles[i]->loadFromImage(img[i]);
		delete perlin[i];
	}
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
	int iter = 4;
	int w = width;
	int h = height;

	map.create(w, h, sf::Color::Black);

	points.resize(w, vector<int>(h, 0));
	maps.resize(w, vector<MapTile *>(h, NULL));

	for (int y = 0; y < w; ++y) {//Loops to loop trough all the pixels
		for (int x = 0; x < h; ++x) {

			int height = heightMap[x][y];
			int rain = rainMap[x][y];

			if (height <= 75) {
				points[x][y] = 0; // water
			}
			else if (height <= 78) { //sand
				points[x][y] = 1;
			}
			else if (height <= 135) { //lower terrain
				if (rain <= 50) {
					points[x][y] = 2; //desert
				}
				else if (rain <= 75) {
					points[x][y] = 3; //grassland
				}
				else {
					points[x][y] = 4; //tropical forest
				}
			}
			else if (height <= 180) { //
				if (rain <= 60) {
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

void MapGenerator::loadMap(int startX, int  startY, int  endX, int endY) {
	int startXX = startX;
	int startYY = startY;
	int endXX = endX;
	int endYY = endY;

	if (startX > 0) {
		--startXX;
	}

	if (endX < width - 1) {
		++endXX;
	}

	if (startY > 0) {
		--startYY;
	}

	if (endY > 0) {
		++endYY;
	}

	for (int i = startXX; i < endXX; ++i) {
		for (int j = startYY; j < endYY; ++j) {
			if (maps[i][j]) {
				delete maps[i][j];
				maps[i][j] = NULL;
			}

			if (i < startX || j < startY || i > endX || j > endY) {

			}

			else {

				if (!(maps[i][j])) {

					maps[i][j] = new MapTile();
					maps[i][j]->setTexture(*tiles[ (int)(8 + 8 *sin(j*i)) % 16]);
					maps[i][j]->setColor(col[points[i][j]]);
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

			//if (maps[i][j].isInitilaized()) {
			//	if (maps[i][j].getTexture()  == NULL) {
			//maps[i][j].setTexture(*tiles[points[i][j]]);
			//}
			//maps[i][j].setTexture(tiles[points[i][j]]);
			//loadMap(maps[i][j], tiles[points[i][j]]);
			//threads.push_back( thread(loadMap, maps[i][j], tiles[points[i][j]]));
			//threads[(i - startX)*(endX - startX) + (j - startY)].join();
			//if (maps[i][j].getTexture() != new Texture()) {
			if (maps[i][j]) {
				maps[i][j]->setPosition(i*scale + position.x, j*scale + position.y);
				target->draw(*maps[i][j]);
			}
		}
	}
}

sf::Image MapGenerator::GetMap() {

	map.create(width, height, sf::Color::Black);

	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			map.setPixel(i, j, col[points[i][j]]);
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