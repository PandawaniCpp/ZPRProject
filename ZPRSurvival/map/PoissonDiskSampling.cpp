#include "PoissonDiskSampling.h"

PoissonDiskSampling::PoissonDiskSampling(float width, float height, WorldMap* map) {
	mapHeight = height;
	mapWidth = width;
	srand(DEFAULT_SEED);
	ilosc = 1;
	Logger::getInstance() << "Poisson - start resize";
	Logger::getInstance() << std::endl;
	positions.resize((width / (DISTANCE / SQRT2)), std::vector<std::vector<sf::Vector2f*>>(height / (DISTANCE / SQRT2), std::vector<sf::Vector2f*>(0)));
	Logger::getInstance() << "Poisson - random points";
	Logger::getInstance() << std::endl;
	objectsPosition(map);
	Logger::getInstance() << "Poisson - finito est with score " << ilosc;
	Logger::getInstance() << std::endl;

}


PoissonDiskSampling::~PoissonDiskSampling() {
}

void PoissonDiskSampling::objectsPosition(WorldMap* map) {
	float minDistance = DISTANCE;

	std::vector <sf::Vector2f*> activePoints;
	//contenner in witch we are putting ceils with points.
	Grid grid;


	float cellSize = minDistance / SQRT2;
	grid.resize((mapWidth / cellSize), std::vector<bool>((mapHeight / cellSize), false));

	sf::Vector2f* firstPoint = randPoint();
	sf::Vector2i baseGrid;
	baseGrid = getGrid(firstPoint, cellSize);
	activePoints.push_back(firstPoint);

	positions[baseGrid.x][baseGrid.y].push_back(firstPoint);
	grid[baseGrid.x][baseGrid.y] = true;
	while (!activePoints.empty()) {

		sf::Vector2f* basePoint = (*activePoints.begin());
		baseGrid = getGrid(basePoint, cellSize);
		int z = KMAX;
		for (int i = 0; i < z; ++i) {

			sf::Vector2f* neighbour = randNeighbour(basePoint, minDistance);
			sf::Vector2i neighbourGrid = getGrid(neighbour, cellSize);

			if (neighbour->x>0 && neighbour->y > 0 && neighbour->x < mapWidth && neighbour->y < mapHeight) {
				if (map->getMap(neighbour->x, neighbour->y, 0)>127) {
					// if ok add to active, grid and objectsPosition
					if (checkNeighbour(neighbour, minDistance, grid, positions)) {
						activePoints.push_back(neighbour);
						grid[neighbourGrid.x][neighbourGrid.y] = true;
						positions[neighbourGrid.x][neighbourGrid.y].push_back(neighbour);
						ilosc++;
					}
				}
			}
		}

		// delete previous random from active
		activePoints.erase(activePoints.begin());
	}
}

sf::Vector2f* PoissonDiskSampling::randPoint() {

	float y = static_cast <float> (mapHeight / 2);

	float x = static_cast <float> (mapWidth / 2);
	return new sf::Vector2f(x, y);

}

sf::Vector2i PoissonDiskSampling::getGrid(const sf::Vector2f* point, const float & size) {
	return sf::Vector2i(static_cast<int>(point->x / size), static_cast<int>(point->y / size));

}

sf::Vector2f* PoissonDiskSampling::randNeighbour(const sf::Vector2f* basePoint, const float & distance) {
	//while position is not between f and 2f, randomize
	float r;
	float alpha;
	float x = 0;
	float y = 0;

	r = static_cast <float> (rand() % static_cast<int> (distance));
	r += distance;
	alpha = static_cast <float> (rand() % 1000);
	alpha *= PI;
	alpha /= 500;
	x = basePoint->x + r* sin(alpha);
	y = basePoint->y - r* cos(alpha);


	return new sf::Vector2f(x, y);

}

bool PoissonDiskSampling::checkNeighbour(const sf::Vector2f* candidate, const float & minRange, const Grid & gridVector, const Positions& positions) {
	bool yesItIs = false;
	float cellSize = minRange / SQRT2;
	int maxx = mapWidth / cellSize;
	int maxy = mapHeight / cellSize;

	sf::Vector2i candidateGrid = getGrid(candidate, cellSize);
	if (gridVector[candidateGrid.x][candidateGrid.y])
		return yesItIs;

	//zasieg +/- 3 gridow
	for (int x = candidateGrid.x - 3; x <= candidateGrid.x + 3; ++x) {
		for (int y = candidateGrid.y - 3; y <= candidateGrid.y + 3; ++y) {
			if (x >= 0 && y >= 0 && x < maxx && y < maxy)
				for (auto& iterator : positions[x][y])
					if (sqrt((candidate->x - (*iterator).x)*(candidate->x - (*iterator).x) + (candidate->y - (*iterator).y)*(candidate->y - (*iterator).y)) < minRange)
						return yesItIs;

		}
	}

	yesItIs = true;
	return yesItIs;
}

		
std::vector<std::vector<std::vector<sf::Vector2f*>>>& PoissonDiskSampling::getPositions() {
	return positions;
}