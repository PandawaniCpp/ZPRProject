#include "MidpointDisplacementNoise.h"


MidpointDisplacementNoise::MidpointDisplacementNoise(int width, int height, int step) {

	pointsTab_.resize(width, vector<int>(height, 0));
	width_ = width;
	height_ = height;
	int iter = 4;
	for (int i = step; i < width; i += step) {
		for (int j = step; j < width; j += step) {
			pointsTab_[i][j] = rand() % 255;
			if (i == width / 2 && j == height / 2) {
				pointsTab_[i][j] = 128;
			}
		}
	}

	int r = 14;

	while (step > 1) {
		int x1, x2, y1, y2;
		r -= 2;
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
					x1 = 0;
				}
				else if (i + step / 2 >= width) {
					x2 = 0;
				}

				if (j - step / 2 < 0) {
					y1 = 0;

				}
				else if (j + step / 2 >= height) {
					y2 = 0;
				}
				pointsTab_[i][j] = (pointsTab_[x1][y1] +
									pointsTab_[x2][y1] +
									pointsTab_[x1][y2] +
									pointsTab_[x2][y2]) / 4.0 + rand() % (r + 1) - r / 2;
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
					x1 = 0;
				}
				else if (i + step / 2 >= width) {
					x2 = 0;
				}

				if (j - step / 2 < 0) {
					y1 = 0;

				}
				else if (j + step / 2 >= height) {
					y2 = 0;
				}


				pointsTab_[i][j] = (pointsTab_[i][y1] +
									pointsTab_[x1][j] +
									pointsTab_[i][y2] +
									pointsTab_[x2][j]) / 4.0 + rand() % (r + 1) - r / 2;
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