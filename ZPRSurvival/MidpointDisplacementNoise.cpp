#include "MidpointDisplacementNoise.h"

int MidpointDisplacementNoise::CalculateNoise(int x, int y) {

	int n = x + (offset + y) * 57;
	n = (n << 13) ^ n;
	int nn = (n*(n*n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
	return ((double)nn / 1073741824.0)*127.5;
}

MidpointDisplacementNoise::MidpointDisplacementNoise(int width, int height, int step, bool randomize, bool island, bool invert) {
	int r;
	int iter = 6;
	offset = rand() % 1000;
	if (invert) {
		pointsTab_.resize(width, vector<int>(height, 255));
	}
	else {
		pointsTab_.resize(width, vector<int>(height, 0));
	}
	width_ = width;
	height_ = height;
	int i;
	if (island) {
		i = step;
	}
	else {
		i = 0;
	}
	for ( ; i < width; i += step) {
		int j;
		if (island) {
			j = step;
		}
		else {
			j = 0;
		}
		for ( ; j < width; j += step) {
			pointsTab_[i][j] = CalculateNoise(i, j);
			
			if (i == width / 2 && j == height / 2 && island) {
				pointsTab_[i][j] = 128;
			}

			if (invert) {
				pointsTab_[i][j] = 255 - pointsTab_[i][j];
			}
		}
	}

	if (randomize) {
		r = 80;
	}
	else {
		r = 0;
	}
	
	while (step > 1) {
		int x1, x2, y1, y2;
		r /= 2;
		if (r < 0) {
			r = 0;
		}
		//Square step
		for (int i = step / 2; i < width; i += step) {
			for (int j = step / 2; j < height; j += step) {

				x1 = i - step / 2;
				x2 = i + step / 2;
				y1 = j - step / 2;
				y2 = j + step / 2;

				if (i - step / 2 < 0) {
					x1 = width - step / 2;
				}
				else if (i + step / 2 >= width) {
					x2 = 0;
				}

				if (j - step / 2 < 0) {
					y1 = height - step / 2;

				}
				else if (j + step / 2 >= height) {
					y2 = 0;
				}

				pointsTab_[i][j] = (pointsTab_[x1][y1] +
									pointsTab_[x2][y1] +
									pointsTab_[x1][y2] +
									pointsTab_[x2][y2]) / 4.0 + CalculateNoise(i, j) % (r + 1) - r / 2;
	
				if (pointsTab_[i][j] > 255.0) {
					pointsTab_[i][j] = 255.0;
				}
				else if (pointsTab_[i][j] < 0.0) {
					pointsTab_[i][j] = 0.0;
				}
			}
		}

		//Diamond step
		for (int i = 0; i < width; i += step / 2) {
			for (int j = (step / 2)*((1 + i / (step / 2)) % 2); j < height; j += step) {

				x1 = i - step / 2;
				x2 = i + step / 2;
				y1 = j - step / 2;
				y2 = j + step / 2;

				if (i - step / 2 < 0) {
					x1 = width - step / 2;
				}
				else if (i + step / 2 >= width) {
					x2 = 0;
				}

				if (j - step / 2 < 0) {
					y1 = height - step / 2;

				}
				else if (j + step / 2 >= height) {
					y2 = 0;
				}


				pointsTab_[i][j] = (pointsTab_[i][y1] +
									pointsTab_[x1][j] +
									pointsTab_[i][y2] +
									pointsTab_[x2][j]) / 4.0 + CalculateNoise(i, j) % (r + 1) - r / 2;
				if (pointsTab_[i][j] > 255.0) {
					pointsTab_[i][j] = 255.0;
				}
				else if (pointsTab_[i][j] < 0.0) {
					pointsTab_[i][j] = 0.0;
				}
			}
		}
		step /= 2;
	}
	for (int k = 0; k < iter; k++) {
		vector< vector<int>> pointsTab2_(pointsTab_);
		for (int i = 1; i < width - 1; i++) {
			for (int j = 1; j < width - 1; j++) {
				pointsTab2_[i][j] = (pointsTab_[i - 1][j - 1] +
									 pointsTab_[i - 1][j] +
									 pointsTab_[i - 1][j + 1] +
									 pointsTab_[i][j - 1] +
									 pointsTab_[i][j + 1] +
									 pointsTab_[i + 1][j - 1] +
									 pointsTab_[i - 1][j] +
									 pointsTab_[i + 1][j + 1]) / 8.0;
			}
		}
		pointsTab_ = pointsTab2_;
	}
}


MidpointDisplacementNoise::~MidpointDisplacementNoise() {
}

void MidpointDisplacementNoise::AddGradient() {
	int rotation = rand() % 360;
	int w = width_;
	int h = height_;
	double gradVec[2][2];

	if (rotation >= 0) {
		gradVec[0][0] = rotation / 90.0;
		gradVec[0][1] = 1;
		gradVec[1][0] = 0;
		gradVec[1][1] = 1 - rotation / 90.0;
	}

	if (rotation >= 90) {
		gradVec[0][0] = 1;
		gradVec[0][1] = 1 - (rotation - 90) / 90.0;
		gradVec[1][0] = (rotation - 90) / 90.0;
		gradVec[1][1] = 0;
	}

	if (rotation >= 180) {
		gradVec[0][0] = 1 - (rotation - 180) / 90.0;
		gradVec[0][1] = 0;
		gradVec[1][0] = 1;
		gradVec[1][1] = (rotation - 180) / 90.0;
	}

	if (rotation >= 270) {
		gradVec[0][0] = 0;
		gradVec[0][1] = (rotation - 270) / 90.0;
		gradVec[1][0] = 1 - (rotation - 270) / 90.0;
		gradVec[1][1] = 1;
	}

	for (int y = 0; y < h; y++) {//Loops to loop trough all the pixels
		for (int x = 0; x < w; x++) {
			pointsTab_[x][y] *= (gradVec[0][0] * ((double)(w - x) / (double)(w)) + gradVec[1][0] * ((double)(x) / (double)(w))) * ((double)(h - y) / (double)(h)) +
				(gradVec[0][1] * (double)(w - x) / (double)(w)+gradVec[1][1] * (double)(x) / (double)(w)) * ((double)(y) / (double)(h));
		}
	}

}

vector<vector<int>> MidpointDisplacementNoise::GetVector() {
	return pointsTab_;
}

Image MidpointDisplacementNoise::GetImage() {
	Image img;
	img.create(width_, height_, sf::Color::Black);

	for (int i = 0; i < width_; i++) {
		for (int j = 0; j < height_; j++) {
			img.setPixel(i, j, sf::Color(pointsTab_[i][j], pointsTab_[i][j], pointsTab_[i][j]));
		}
	}
	return img;
}