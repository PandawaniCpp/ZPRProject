#include "RandomNoise.h"
#include <cmath>
#include <ctime>

RandomNoise::RandomNoise() {
}

RandomNoise::RandomNoise(int const & w, int const & h, int const & z, double const & p, int const & octaves, int const & offset, bool bIsland) {
	this->width = w;
	this->height = h;
	this->zoom = z;
	this->p = p;
	this->octaves = octaves;
	this->offset = offset;

	heur.loadFromFile("./resources/map/Map.png");

	mapVec.resize(width, vector<int>(height, 200));
	noiseImg.create(width, height, sf::Color::Black);//Create an empty image.

	int color;
	float getNoise, frequency, amplitude;

	for (int y = 0; y < height; y++) {//Loops to loop trough all the pixels
		for (int x = 0; x < width; x++) {

			getNoise = 0.0f;

			float distanceFromCenter = 0.3f;

			if (x > 0.6f*width) {
				distanceFromCenter -= 1.5f*(25.0f / 4.0f) * pow((x - width*0.6f), 2) / pow(width, 2);
			}
			else if (x < 0.4f*width) {
				distanceFromCenter -= 1.5f*(25.0f / 4.0f) * pow((width*0.4f - x), 2) / pow(width, 2);
			}
			if (y > 0.6f*height) {
				distanceFromCenter -= 1.5f*(25.0f / 4.0f) * pow((y - height*0.6f), 2) / pow(height, 2);
			}
			else if (y < 0.4f*height) {
				distanceFromCenter -= 1.5f*(25.0f / 4.0f) * pow((height*0.4f - y), 2) / pow(height, 2);
			}

			if (distanceFromCenter < -1.0f) {
				//distanceFromCenter = -1.5f;
			}
			if (bIsland) {
				getNoise = distanceFromCenter;
			}
			for (int a = 0; a < octaves + 1; a++) {
				frequency = pow(2, a);//This increases the frequency with every loop of the octave.
				amplitude = pow(p, a + 1);//This decreases the amplitude with every loop of the octave.
				getNoise += noise(((double)x)*frequency / zoom, ((double)y)*frequency / zoom)*amplitude;//This uses our perlin noise functions. It calculates all our zoom and frequency and amplitude
			}//                                         It gives a decimal value, you know, between the pixels. Like 4.2 or 5.1

			color = (int)((getNoise*128.0f) + 128.0f);//Convert to 0-256 values.
			if (color > 255.0f) {
				color = 255.0f;
			}

			if (color <= 0.0f) {
				color = 0.0f;
			}

			mapVec[x][y] = color;// *distanceFromCenter;
			noiseImg.setPixel(x, y, sf::Color(mapVec[x][y], mapVec[x][y], mapVec[x][y]));
		}

	}

}
void RandomNoise::calculateIsland(bool bIsland) {

}

RandomNoise::~RandomNoise() {
}

//Pseudorandom number generator, return number between -1 and 1
inline double RandomNoise::calculateNoise(double x, double y) {

	int n = (int)x + (offset + (int)y) * 57;
	n = (n << 13) ^ n;
	int nn = (n*(n*n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
	return 1.0 - ((double)nn / 1073741824.0);
}

inline double RandomNoise::interpolate(double a, double b, double x) {
	double ft = x * 3.1415927;
	double f = (1.0 - cos(ft))* 0.5;
	return a*(1.0 - f) + b*f;
}

double RandomNoise::noise(double x, double y) {
	double floorx = (double)((int)x);//This is kinda a cheap way to floor a double integer.
	double floory = (double)((int)y);
	double s, t, u, v;//Integer declaration
	s = calculateNoise(floorx, floory);
	t = calculateNoise(floorx + 1, floory);
	u = calculateNoise(floorx, floory + 1);//Get the surrounding pixels to calculate the transition.
	v = calculateNoise(floorx + 1, floory + 1);
	double int1 = interpolate(s, t, x - floorx);//Interpolate between the values.
	double int2 = interpolate(u, v, x - floorx);//Here we use x-floorx, to get 1st dimension. Don't mind the x-floorx thingie, it's part of the cosine formula.
	return interpolate(int1, int2, y - floory);//Here we use y-floory, to get the 2nd dimension.
}

sf::Image & RandomNoise::getImage() {
	return noiseImg;
}

vector< vector<int>> RandomNoise::getVector() {
	return mapVec;
}

sf::Image RandomNoise::getZoomedTile(int & x, int & y, int & size, int & moisture, int & zoom, double & p) {

	int color;
	float getNoise, frequency, amplitude;
	sf::Image image;


	int oct = octaves;
	double pp = p;

	int s = 100;

	int w = width*s;
	int h = height*s;

	image.create(s, s, sf::Color::Green);//Create an empty image.

	for (int i = 0; i < s; i++) {//Loops to loop trough all the pixels
		for (int j = 0; j < s; j++) {
			int ii = i + x*s;
			int jj = j + y*s;

			getNoise = 0.0f;// ((float)mapVec[x][y] - 128.0f) / 128.0f

			double distanceFromCenter = 0.5;


			if (ii > 0.6*w) {
				distanceFromCenter -= 1.5*(25.0 / 4.0) * pow((ii - w*0.6), 2) / pow(w, 2);
			}
			else if (ii < 0.4*w) {
				distanceFromCenter -= 1.5f*(25.0 / 4.0) * pow((w*0.4 - ii), 2) / pow(w, 2);
			}
			if (jj > 0.6*h) {
				distanceFromCenter -= 1.5*(25.0 / 4.0) * pow((jj - h*0.6), 2) / pow(h, 2);
			}
			else if (jj < 0.4*h) {
				distanceFromCenter -= 1.5*(25.0 / 4.0) * pow((h*0.4 - jj), 2) / pow(h, 2);
			}

			if (distanceFromCenter < -1.0) {
				//distanceFromCenter = -1.0f;
			}

			getNoise = distanceFromCenter;

			for (int a = 0; a < oct; a++) {
				frequency = pow(2, a);//This increases the frequency with every loop of the octave.
				amplitude = pow(pp, a + 1);//This decreases the amplitude with every loop of the octave.
				getNoise += noise(((double)ii)*frequency / zoom, ((double)jj)*frequency / zoom)*amplitude;//This uses our perlin noise functions. It calculates all our zoom and frequency and amplitude
			}                                       //  It gives a decimal value, you know, between the pixels. Like 4.2 or 5.1

			color = (int)((getNoise*128.0f) + 128.0f);//Convert to 0-256 values.
			if (color > 255.0f) {
				color = 255.0f;
			}

			if (color <= 0.0f) {
				color = 0.0f;
			}
			//color *= distanceFromCenter;
			image.setPixel(i, j, heur.getPixel(moisture, color));
			//image.setPixel(i, j, sf::Color(color,color,color));
		}

	}

	return image;
}

sf::Color RandomNoise::heury(int h, int m) {
	return sf::Color(h, h, h);
	if (h <= 80) {
		return sf::Color(0, 18, 25);
	}
	else if (h <= 90) { //sand
		return sf::Color(200, 180, 120);
	}
	else if (h <= 160) { //lower terrain
		if (m <= 80) {
			return sf::Color(180, 120, 100); //desert
		}
		else if (m <= 130) {
			return sf::Color(100, 120, 50); //grassland
		}
		else {
			return sf::Color(20, 80, 20); //tropical forest
		}
	}
	else if (h <= 200) { //
		if (m <= 100) {
			return sf::Color(180, 120, 100); //desert
		}
		else if (m <= 140) {
			return sf::Color(100, 120, 50); //grassland
		}
		else {
			return sf::Color(50, 100, 30); // forest
		}
	}
	//	else if (height <= 160) {
	//		points[x][y] = 6; //mountains
	//	}
	else {
		return sf::Color(30, 30, 30); //mountains
	}
}