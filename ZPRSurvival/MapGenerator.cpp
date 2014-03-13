#include "MapGenerator.h"


MapGenerator::MapGenerator(int w, int h) {

	MidpointDisplacementNoise heightNoise(w, h, w/8, true, true, false);
	MidpointDisplacementNoise tempNoise(w, h, w/2, true, true, true);
	MidpointDisplacementNoise forestNoise(w, h, w/4, false, true, false);
	MidpointDisplacementNoise rainNoise(w, h, w/4, false, false, false);

	tempNoise.AddGradient();
	this->Calculate(heightNoise.GetVector(), tempNoise.GetVector(), rainNoise.GetVector(), forestNoise.GetVector());
}


MapGenerator::~MapGenerator() {
}

void MapGenerator::Calculate(vector<vector<int>> heightMap, vector<vector<int>> tempMap, vector<vector<int>> rainMap, vector<vector<int>> forestMap) {
	int iter = 4;
	int w = heightMap[0].size();
	int h = heightMap.size();

	map.create(h, w, sf::Color::Black);

	points.resize(h, vector<int>(w, 0));


	for (int y = 0; y < w; y++) {//Loops to loop trough all the pixels
		for (int x = 0; x < h; x++) {

			int height = heightMap[x][y];
			int temperature = tempMap[x][y];
			int rain = rainMap[x][y];
			int forest = forestMap[x][y];

			if (height <= 75) {
				points[x][y] = 15; // water
			}
			else if (height <= 90) { //sand
				points[x][y] = 14;
			}
			else if (height <= 175) { //
				if (temperature <= 80) {
					if (forest <= 60) {
						if (rain <= 150) {
							points[x][y] = 13; //pustkowie 
						}
						else {
							points[x][y] = 12; //krzewy iglaste
						}
					}
					else {
						if (rain <= 20) {
							points[x][y] = 13; //pustkowie
						}
						else if (rain <= 100) {
							points[x][y] = 12; //krzewy iglaste
						}
						else {
							points[x][y] = 11; //las iglasty
						}
					}
				}
				else if (temperature <= 140) {
					if (forest <= 60) {
						if (rain <= 20) {
							points[x][y] = 5; //pustynia
						}
						else if (rain <= 100) {
							points[x][y] = 10; //trawka 
						}
						else if (rain <= 180) {
							points[x][y] = 9; //krzewy
						}
						else {
							points[x][y] = 6; //bagno
						}
					}
					else {
						if (rain <= 20) {
							points[x][y] = 5; //pustynia
						}
						else if (rain <= 100) {
							points[x][y] = 9; //step
						}
						else {
							points[x][y] = 8; //las liœciasty
						}
					}
				}
				else {
					if (forest <= 60) {
						if (rain <= 60) {
							points[x][y] = 5; //pustynia
						}
						else if (rain <= 100) {
							points[x][y] = 7; //trawka w tropiku
						}
						else {
							points[x][y] = 6; //bagno
						}
					}
					else {
						if (rain <= 60) {
							points[x][y] = 5; //pustynia
						}
						else if (rain <= 120) {
							points[x][y] = 4; //sawanna
						}
						else {
							points[x][y] = 3; //jungla
						}
					}
				}
			}
			else if (height <= 200) {
				points[x][y] = 2; //rocks
			}
			else {
				points[x][y] = 1; //mountains
			}
		}
	}

}


sf::Image MapGenerator::GetMap() {

	int w = map.getSize().x;
	int h = map.getSize().y;

	for (int y = 0; y < w; y++) {//Loops to loop trough all the pixels
		for (int x = 0; x < h; x++) {
			if (points[x][y] == 1) {
				map.setPixel(x, y, sf::Color(50, 40, 0)); // ((int)((r / 255.0)*(double)color), (int)((g / 255.0)*(double)color), (int)((b / 255.0)*(double)color)));//This colours the image with the RGB values
			}
			else if (points[x][y] == 2) {
				map.setPixel(x, y, sf::Color(50, 50, 50)); // ((int)((r / 255.0)*(double)color), (int)((g / 255.0)*(double)color), (int)((b / 255.0)*(double)color)));//This colours the image with the RGB values
			}
			else if (points[x][y] == 3) {
				map.setPixel(x, y, sf::Color(60, 40, 0)); // ((int)((r / 255.0)*(double)color), (int)((g / 255.0)*(double)color), (int)((b / 255.0)*(double)color)));//This colours the image with the RGB values
			}
			else if (points[x][y] == 4) {
				map.setPixel(x, y, sf::Color(60, 40, 40)); // ((int)((r / 255.0)*(double)color), (int)((g / 255.0)*(double)color), (int)((b / 255.0)*(double)color)));//This colours the image with the RGB values
			}
			else if (points[x][y] == 5) {
				map.setPixel(x, y, sf::Color(180, 160, 0)); // ((int)((r / 255.0)*(double)color), (int)((g / 255.0)*(double)color), (int)((b / 255.0)*(double)color)));//This colours the image with the RGB values
			}
			else if (points[x][y] == 6) {
				map.setPixel(x, y, sf::Color(70, 50, 0)); // ((int)((r / 255.0)*(double)color), (int)((g / 255.0)*(double)color), (int)((b / 255.0)*(double)color)));//This colours the image with the RGB values
			}
			else if (points[x][y] == 7) {
				map.setPixel(x, y, sf::Color(20, 170, 0)); // ((int)((r / 255.0)*(double)color), (int)((g / 255.0)*(double)color), (int)((b / 255.0)*(double)color)));//This colours the image with the RGB values
			}
			else if (points[x][y] == 8) {
				map.setPixel(x, y, sf::Color(20, 180, 20)); // ((int)((r / 255.0)*(double)color), (int)((g / 255.0)*(double)color), (int)((b / 255.0)*(double)color)));//This colours the image with the RGB values
			}
			else if (points[x][y] == 9) {
				map.setPixel(x, y, sf::Color(100, 80, 0)); // ((int)((r / 255.0)*(double)color), (int)((g / 255.0)*(double)color), (int)((b / 255.0)*(double)color)));//This colours the image with the RGB values
			}
			else if (points[x][y] == 10) {
				map.setPixel(x, y, sf::Color(40, 180, 40)); // ((int)((r / 255.0)*(double)color), (int)((g / 255.0)*(double)color), (int)((b / 255.0)*(double)color)));//This colours the image with the RGB values
			}
			else if (points[x][y] == 11) {
				map.setPixel(x, y, sf::Color(10, 60, 10)); // ((int)((r / 255.0)*(double)color), (int)((g / 255.0)*(double)color), (int)((b / 255.0)*(double)color)));//This colours the image with the RGB values
			}
			else if (points[x][y] == 12) {
				map.setPixel(x, y, sf::Color(50, 100, 50)); // ((int)((r / 255.0)*(double)color), (int)((g / 255.0)*(double)color), (int)((b / 255.0)*(double)color)));//This colours the image with the RGB values
			}
			else if (points[x][y] == 13) {
				map.setPixel(x, y, sf::Color(140, 150, 40)); // ((int)((r / 255.0)*(double)color), (int)((g / 255.0)*(double)color), (int)((b / 255.0)*(double)color)));//This colours the image with the RGB values
			}
			else if (points[x][y] == 14) {
				map.setPixel(x, y, sf::Color(200, 230, 40)); // ((int)((r / 255.0)*(double)color), (int)((g / 255.0)*(double)color), (int)((b / 255.0)*(double)color)));//This colours the image with the RGB values
			}
			else {
				map.setPixel(x, y, sf::Color(18, 10, 40)); // ((int)((r / 255.0)*(double)color), (int)((g / 255.0)*(double)color), (int)((b / 255.0)*(double)color)));//This colours the image with the RGB values
			}
		}
	}
	return map;
}