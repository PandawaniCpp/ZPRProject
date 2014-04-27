#include "PoissonDiskSampling.h"

PoissonDiskSampling::PoissonDiskSampling(float width, float height, WorldMap* map) {
	mapHeight = height;
	mapWidth = width;
	srand(DEFAULT_SEED);
	ilosc = 1;
	Logger::getInstance() << "Lets start this shit";
	Logger::getInstance() << std::endl;
	positions.resize((width / (KMAX / SQRT2)), std::vector<std::vector<sf::Vector2f>>(height / (KMAX / SQRT2), std::vector<sf::Vector2f>(0)));
	Logger::getInstance() << "Lets start this shit";
	Logger::getInstance() << std::endl;
	objectsPosition(map);
	Logger::getInstance() << "finito est with score " << ilosc;
	Logger::getInstance() << std::endl;

}


PoissonDiskSampling::~PoissonDiskSampling() {
}

void PoissonDiskSampling::objectsPosition(WorldMap* map) {
	float minDistance = DISTANCE;

	std::vector <sf::Vector2f> activePoints;
	//contenner in witch we are putting ceils with points.
	Grid grid;


	float cellSize = minDistance / SQRT2;
	grid.resize((mapWidth / cellSize), std::vector<bool>((mapHeight / cellSize), false));
	//computing size of our grid
	//int gridHeight = static_cast<int>(mapHeight / cellSize);
	//int gridWidth = static_cast<int>(mapWidth / cellSize);


	sf::Vector2f firstPoint = randPoint();
	////logger //log = //logger::getInstance();
	//log << firstPoint.x;
	//log << ";";
	//log << firstPoint.y;
	//log << endl;
	sf::Vector2i baseGrid;
	baseGrid = getGrid(firstPoint, cellSize);
	activePoints.push_back(firstPoint);
	
	positions[baseGrid.x][baseGrid.y].push_back(firstPoint);
	grid[baseGrid.x][baseGrid.y] = true;
	while (!activePoints.empty()) {
		
		//select random from active
		//sf::Vector2f basePoint = randomActive(activePoints);
		sf::Vector2f basePoint = (*(activePoints.begin()));
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
		baseGrid = getGrid(basePoint, cellSize);
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
				if (map->getMap(neighbour.x, neighbour.y, 0)>127) {
						// if ok add to active, grid and objectsPosition
						if (checkNeighbour(neighbour, minDistance, grid, positions)) {
							activePoints.push_back(neighbour);
							grid[neighbourGrid.x][neighbourGrid.y] = true;
							positions[neighbourGrid.x][neighbourGrid.y].push_back(neighbour);
							ilosc++;
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
				}
				//if (occupiedNeighbours == 8)
				//break;
			}


			// delete previous random from active
			activePoints.erase(activePoints.begin());
			//activePoints.pop_back();
			//deleteBasePoint(activePoints, basePoint);
			//
		}
	}

	sf::Vector2f PoissonDiskSampling::randPoint() {

		float y = static_cast <float> (mapHeight / 2);

		float x = static_cast <float> (mapWidth / 2);
		return sf::Vector2f(x, y);

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
	/*    if ((iter.x == grid.x) && (iter.y == grid.y - 1 || iter.y == grid.y + 1)
	++i;
	}
	return i;

	}
	*/
	sf::Vector2f PoissonDiskSampling::randNeighbour(const sf::Vector2f & basePoint, const float & distance) {
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
		x = basePoint.x + r* sin(alpha);
		y = basePoint.y - r* cos(alpha);


		return sf::Vector2f(x, y);

	}

		bool PoissonDiskSampling::checkNeighbour(const sf::Vector2f & candidate, const float & minRange, const Grid & gridVector, const Positions& positions) {
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
							if (sqrt((candidate.x - iterator.x)*(candidate.x - iterator.x) + (candidate.y - iterator.y)*(candidate.y - iterator.y)) < minRange)
								return yesItIs;

						}
					}
				

				/*
				for (auto& iterator : positions) {
				sf::Vector2i pointGrid = getGrid(iterator, cellSize);
				// checking if grid is close to candidate's grid
				if (abs(pointGrid.x - candidateGrid.x <= 2) && abs(pointGrid.y - candidateGrid.y <= 2)) {
				// if yes, check if it is far enough to place a point
				if (sqrt((candidate.x - iterator.x)*(candidate.x - iterator.x) + (candidate.y - iterator.y)*(candidate.y - iterator.y)) < minRange)
				return yesItIs;
				}
				*/



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

				//    activeVector.erase(iter);
				break;
				}
				}*/
			}

			void PoissonDiskSampling::drawlog() {
				Logger log = Logger::getInstance();
				log << "no jestem misku ;)";
				log << std::endl;
				/*
				for (auto& iterator : positions){
				log << " x: ";
				log << iterator.x;
				log << " x: ";
				log << iterator.y;
				log << std::endl;

				log << " x: ";
				log << iterator.x;
				log << " x: ";
				log << iterator.y;
				log << std::endl;
				}
				*/

			}

std::vector<std::vector<std::vector<sf::Vector2f>>>& PoissonDiskSampling::getPositions() {
	return positions;
}