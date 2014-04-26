#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "./../interface/Logger.h"

#define SIZE_COUNT 3
#define SQRT2 1.414213
#define KMAX 30
#define PI 3.1415

using namespace sf;
using namespace std;
/*
Poisson Disk Sampling class is a class wich computes positions of all objects inluded in game, like trees, stones, buildings and so on.
It also return in vector size of point (trees are bigger than blades of grass)
*/
class PoissonDiskSampling {
public:
	PoissonDiskSampling(float width, float height);
	~PoissonDiskSampling();
	/*
	generate location data of objects on map
	function returns vector of:
	-position x
	-position y
	-size of drawen object
	*/
	void objectsPosition();
	Vector2f randPoint();
	Vector2i getGrid(const Vector2f & point, const float & size);
	Vector2f randomActive (vector<Vector2f> & activeVector);
	//int checkOccupiedNeighbours(const Vector2i & Grid, const vector<Vector2i> & gridVector);
	Vector2f randNeighbour(const Vector2f & basePoint, const float & distance);
	bool checkNeighbour(const Vector2f & candidate, const float & minRange, const vector<Vector2i> & gridVector, const vector<Vector2f>& positions);
	void deleteBasePoint(vector<Vector2f> & activeVector, const Vector2f & point);
	void drawlog();
	vector<Vector2f> getPositions();

private:
	vector<Vector2f> positions;
	float mapHeight;
	float mapWidth;
};

