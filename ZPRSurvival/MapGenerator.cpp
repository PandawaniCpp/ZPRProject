#include "MapGenerator.h"


MapGenerator::MapGenerator() {
}


MapGenerator::~MapGenerator() {
}

void MapGenerator::Calculate(sf::Image heightMap) {
	map.create(heightMap.getSize().x, heightMap.getSize().y, sf::Color::Black);
	int iter = 4;
	int w = map.getSize().x;
	int h = map.getSize().y;

	points.resize(w, vector<int>(h, 0));


	for (int y = 0; y < w; y++) {//Loops to loop trough all the pixels
		for (int x = 0; x < h; x++) {

			double color = (double)heightMap.getPixel(x, y).r;
			if (color > 255.0) {
				color = 255.0;
			}

			if (color < 25.0) {
				color = 25.0;
			}

			color = color / 255.0;

			if (color <= 0.3) {
				points[x][y] = 16;
			}
			else if (color <= 0.35) {
				points[x][y] = 8;
			}
			else if (color <= 0.6) {
				points[x][y] = 4;
			}
			else {
				points[x][y] = 1;
			}
		}
	}

}


sf::Image MapGenerator::GetMap() {

	int w = map.getSize().x;
	int h = map.getSize().y;

	for (int y = 0; y < w; y++) {//Loops to loop trough all the pixels
		for (int x = 0; x < h; x++) {
			if (points[x][y]  > 8) {
				map.setPixel(x, y, sf::Color(0, 180, 250)); // ((int)((r / 255.0)*(double)color), (int)((g / 255.0)*(double)color), (int)((b / 255.0)*(double)color)));//This colours the image with the RGB values
			}
			else if (points[x][y] > 4) {
				map.setPixel(x, y, sf::Color(400, 400, 220)); // ((int)((r / 255.0)*(double)color), (int)((g / 255.0)*(double)color), (int)((b / 255.0)*(double)color)));//This colours the image with the RGB values
			}
			else if (points[x][y] > 1) {
				map.setPixel(x, y, sf::Color(100, 200, 100)); // ((int)((r / 255.0)*(double)color), (int)((g / 255.0)*(double)color), (int)((b / 255.0)*(double)color)));//This colours the image with the RGB values
			}
			else {
				map.setPixel(x, y, sf::Color(20, 30, 0)); // ((int)((r / 255.0)*(double)color), (int)((g / 255.0)*(double)color), (int)((b / 255.0)*(double)color)));//This colours the image with the RGB values
			}
		}
	}
	return map;
}