#include "PoissonDiskSampling.h"

PoissonDiskSampling::PoissonDiskSampling(float width, float height, WorldMap* map) {
	mapHeight = height;
	mapWidth = width;
	srand(DEFAULT_SEED);
	objectsPosition(map);
}


PoissonDiskSampling::~PoissonDiskSampling() {
}

void PoissonDiskSampling::objectsPosition(WorldMap* map) {
	float minDistance = DISTANCE;

	std::vector <sf::Vector2f> activePoints;
	//contenner in witch we are putting ceils with points.
	std::vector <sf::Vector2i> grid;

	float cellSize = minDistance / SQRT2;
	//computing size of our grid
	//int gridHeight = static_cast<int>(mapHeight / cellSize);
	//int gridWidth = static_cast<int>(mapWidth / cellSize);


	sf::Vector2f firstPoint = randPoint();
	////logger //log = //logger::getInstance();
	//log << firstPoint.x;
	//log << ";";
	//log << firstPoint.y;
	//log << endl;
	activePoints.push_back(firstPoint);
	positions.push_back(firstPoint);
	grid.push_back(getGrid(firstPoint, cellSize));
	//grid.push_back(sf::Vector2i(static_cast<int>(randomPoint.x / cellSize), static_cast<int>(randomPoint.x / cellSize)))

	while (!activePoints.empty()) {
	//select random from active
		sf::Vector2f basePoint = randomActive(activePoints);
		//log << "==========================NOWY PUNKT============================";
		//log << endl;
		//log << "X: ";
		//log << basePoint.x;
		//log << "Y: ";
		//log << basePoint.y;
		//log << endl;
		//int occupiedNeighbours = 0;
		//log << "wchodzem w grida";
		//log << endl;
		sf::Vector2i baseGrid = getGrid(basePoint, cellSize);
		//log << "mam grida";
		//log << endl;
		// changing number of occupied cells around randomActive, max is 8
		//occupiedNeighbours = checkOccupiedNeighbours(baseGrid, grid)
	// for i to k random neighbour and check grid		
		int z = KMAX;
		for (int i = 0; i < z; ++i) {
			
			sf::Vector2f neighbour = randNeighbour(basePoint, minDistance);
			sf::Vector2i neighbourGrid = getGrid(neighbour, cellSize);
			
			//log << "m�j grid:";
			//log << neighbourGrid.x;
			//log << neighbourGrid.y;
			//log << endl;
			if (neighbour.x>0 && neighbour.y > 0 && neighbour.x < mapWidth && neighbour.y < mapHeight) {
				// if ok add to active, grid and objectsPosition
				if (checkNeighbour(neighbour, minDistance, grid, positions)) {
					activePoints.push_back(neighbour);
					grid.push_back(neighbourGrid);
					positions.push_back(neighbour);
					//log << "dobry punkcik:";
					//log << "nr";
					//log << activePoints.size();
					//log << neighbour.x;
					//log << neighbour.y;
					//log << endl;
					//++occupiedNeighbours;
				}
				else {
					//log << "z�y punkcik:";
					//log << neighbour.x;
					//log << neighbour.y;
					//log << endl;

				}
			}
			//if (occupiedNeighbours == 8)
				//break;
		}

		
	// delete previous random from active
		deleteBasePoint(activePoints, basePoint);
	//
	}

	Logger::getInstance() << positions.size();
}

sf::Vector2f PoissonDiskSampling::randPoint() {

	float y = static_cast <float> (rand() %static_cast<int> (mapHeight));

	float x = static_cast <float> (rand() % static_cast<int> (mapWidth));
	return sf::Vector2f (x,y);

}

sf::Vector2i PoissonDiskSampling::getGrid(const sf::Vector2f & point, const float & size) {
	return sf::Vector2i(static_cast<int>(point.x / size), static_cast<int>(point.y / size));

}

sf::Vector2f PoissonDiskSampling::randomActive(std::vector<sf::Vector2f>& activeVector) {
	int length = activeVector.size();
	int pos = (rand() % length);
	return activeVector[pos];
}
/*
int PoissonDiskSampling::checkOccupiedNeighbours(const sf::Vector2i & grid, const std::vector<sf::Vector2i> & gridVector){
	int i = 0;
	for (auto& iter : gridVector) {
		/* x = grid, y-neighbours
		y-y
		yxy
		y-y
		*/
		//if (((iter.x == grid.x - 1) || (iter.x == grid.x + 1)) && (iter.y == grid.y - 1 || iter.y == grid.y + 1 || iter.y == grid.y)
			//++i;
		/*
		-y-
		-x-
		-y-
		*/
	/*	if ((iter.x == grid.x) && (iter.y == grid.y - 1 || iter.y == grid.y + 1)
			++i;
	}
	return i;

}
*/
sf::Vector2f PoissonDiskSampling::randNeighbour(const sf::Vector2f & basePoint, const float & distance) {
	//while position is not between f and 2f, randomize
	float r;
	float alpha;
	float x=0;
	float y=0;

	r = static_cast <float> (rand() % static_cast<int> (distance));
	r += distance;
	alpha = static_cast <float> (rand() % 1000);
	alpha *= PI;
	alpha /= 500;
	x = basePoint.x + r* sin(alpha);
	y = basePoint.y - r* cos(alpha);
				
	
	return sf::Vector2f(x, y);

}

bool PoissonDiskSampling::checkNeighbour(const sf::Vector2f & candidate, const float & minRange, const std::vector<sf::Vector2i> & gridVector, const std::vector<sf::Vector2f>& positions) {
	bool yesItIs = false;
	float cellSize = minRange / SQRT2;
	sf::Vector2i candidateGrid = getGrid(candidate, cellSize);
	for (auto& iter : gridVector) {
		if (iter == candidateGrid) {
			return yesItIs;

		}
	}
		for (auto& iterator : positions) {
			sf::Vector2i pointGrid = getGrid(iterator, cellSize);
			// checking if grid is close to candidate's grid
			if (abs(pointGrid.x - candidateGrid.x <= 2) && abs(pointGrid.y - candidateGrid.y <= 2)) {
				// if yes, check if it is far enough to place a point
				if (sqrt((candidate.x - iterator.x)*(candidate.x - iterator.x) + (candidate.y - iterator.y)*(candidate.y - iterator.y)) < minRange)
					return yesItIs;
				//zaraz sie zrobi
			}
		}

		yesItIs = true;
	return yesItIs;
}

void PoissonDiskSampling::deleteBasePoint(std::vector<sf::Vector2f> & activeVector, const sf::Vector2f & point) {
	std::vector<sf::Vector2f>::iterator iterator;
	iterator = activeVector.begin();

	while ((*iterator) != point) {
		++iterator;
	}
	activeVector.erase(iterator);

	/*for (std::vector<sf::Vector2f>::iterator iter = activeVector.begin(); iter != activeVector.end(); ++iter) {
		if ((*iter) == point) {
		
			//	activeVector.erase(iter);
			break;
		}
	}*/
}

void PoissonDiskSampling::drawlog() {
	Logger log = Logger::getInstance();
	log << "no jestem misku ;)";
	log << std::endl;
	for (auto& iterator : positions){
		log << " x: ";
		log << iterator.x;
		log << " x: ";
		log << iterator.y;
		log << std::endl;

	}
}

std::vector<sf::Vector2f>& PoissonDiskSampling::getPositions()
{
	return positions;
}