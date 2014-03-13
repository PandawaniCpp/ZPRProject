#include "PerlinNoise.h"
#include <cmath>
#include <ctime>

PerlinNoise::PerlinNoise(int w, int h, double zoom, double p, int r, int g, int b, int octaves) {
	int color;
	double getnoise, frequency, amplitude;
	srand((int)time(NULL));
	offset =  (int)rand() % 100000;
	mapVec.resize(w, vector<int>(h, 0));
	noise.create(w, h, sf::Color::Black);//Create an empty image.

	for (int y = 0; y < h; y++) {//Loops to loop trough all the pixels
		for (int x = 0; x < w; x++) {

			getnoise = 0;

			for (int a = 0; a < octaves - 1; a++) {
				frequency = pow(2, a);//This increases the frequency with every loop of the octave.
				amplitude = pow(p, a+1);//This decreases the amplitude with every loop of the octave.
				getnoise += Noise(((double)x)*frequency / zoom, ((double)y) / zoom*frequency)*amplitude;//This uses our perlin noise functions. It calculates all our zoom and frequency and amplitude
			}//                                         It gives a decimal value, you know, between the pixels. Like 4.2 or 5.1

			color = (int)((getnoise*128.0) + 128.0);//Convert to 0-256 values.
			if (color > 255) {
				color = 255;
			}

			if (color <= 0) {
				color = 0;
			}

			mapVec[x][y] = color;
		}//                                                          given at the beginning in the function.

	}
}

PerlinNoise::~PerlinNoise() {
}

//Pseudorandom number generator, return number between -1 and 1
inline double PerlinNoise::CalculateNoise(double x, double y) {

	int n = (int)x + (offset + (int)y) * 57;
	n = (n << 13) ^ n;
	int nn = (n*(n*n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
	return 1.0 -((double)nn / 1073741824.0);
}

inline double PerlinNoise::Interpolate(double a, double b, double x) {
	//double ft = x * 3.1415927;
	//double f = (x/2)* 0.5;
	return a*(1.0 - x) + b*x;
}

double PerlinNoise::Noise(double x, double y) {
	double floorx = (double)((int)x);//This is kinda a cheap way to floor a double integer.
	double floory = (double)((int)y);
	double s, t, u, v;//Integer declaration
	s = CalculateNoise(floorx, floory);
	t = CalculateNoise(floorx + 1, floory);
	u = CalculateNoise(floorx, floory + 1);//Get the surrounding pixels to calculate the transition.
	v = CalculateNoise(floorx + 1, floory + 1);
	double int1 = Interpolate(s, t, x - floorx);//Interpolate between the values.
	double int2 = Interpolate(u, v, x - floorx);//Here we use x-floorx, to get 1st dimension. Don't mind the x-floorx thingie, it's part of the cosine formula.
	return Interpolate(int1, int2, y - floory);//Here we use y-floory, to get the 2nd dimension.
}

sf::Image PerlinNoise::GetImage() {
	return noise;
}
