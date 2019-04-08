#include "Road.h"
#include <vector>

Road::Road()
{
	int maxTunnels = MaxTUNNELS;

	glm::vec2 randomDirection;
	glm::vec2 lastDiection;

	//Set the initial values
	for (int i = 0; i < DIMENSIONS; i++) {
		for (int j = 0; j < DIMENSIONS; j++) {
			if (i == 0 || i == DIMENSIONS - 1 || j == 0 || j == DIMENSIONS - 1) {
				road[i][j] = 1;
			}
			else {
				road[i][j] = 0;
			}

			if (j == 0 || j == DIMENSIONS - 1) {
				type[i][j] = 1;
			}
			else {
				type[i][j] == 0;
			}
		}
	}

	//INTENSITY means the maximum number of arbitrary points
	for (int i = 0; i < INTENSITY; i++) {

		std::vector<glm::vec2> greenPoints;

		//Check for green points
		//A green point means that all his neighbours are grass
		//that mean neither of neighbours are road
		//I did this to ensure that the roads are not doubled
		for (int k = 1; k < DIMENSIONS - 1; k++) {
			for (int t = 1; t < DIMENSIONS - 1; t++) {
				if (isAGreenPoint(k, t) == true) {
					greenPoints.push_back(glm::vec2(k, t));
				}
			}
		}

		//Tell the alghoritm when to stop
		if (greenPoints.size() < MINIMUM_GREEN_POINTS) {
			break;
		}

		//Pick a random green point to start from
		int randomGreenPoint = rand() % greenPoints.size();
		int currentRow = greenPoints[randomGreenPoint].x;
		int currentColumn = greenPoints[randomGreenPoint].y;

		//Pick a random direction
		randomDirection = directions[rand() % directions.size()];

		int startRow = currentRow;
		int startColumn = currentColumn;
		glm::vec2 startDirection = randomDirection;

		//This for loop is executed 2 times
		//For every point this for ensure that is goes
		//in 2 directions to create conexity
		for (int i = 0; i < 2; i++) {
			currentRow = startRow;
			currentColumn = startColumn;
			
			if (i == 1) {
				randomDirection = -startDirection;
			}
			bool stop = false;
			int tries = 0;
			bool breakIt = false;
			while (stop == false) {
				stop = true;

				//Dont go back
				while ((randomDirection == -lastDiection) ||
					(randomDirection == lastDiection)) {
					randomDirection = directions[rand() % directions.size()];
				}

				//Pick a random length
				int randomLength = rand() % MaxLENGTH + 1;
				int tunnelLength = 0;

				//Try to create the road
				while (tunnelLength < randomLength) {
					stop = false;
					road[currentRow][currentColumn] = 1;

					//Ensure that there is a valid direction to go
					//if not just stop
					tries++;
					if (tries > 3) {
						breakIt = true;
					}
					if (testNeighbours(randomDirection, currentRow, currentColumn) == false) {
						break;
					}
					tries = 0;

					//Ensure that you are still on the map
					if (((currentRow == 0) && (randomDirection.x == -1)) ||
						((currentColumn == 0) && (randomDirection.y == -1)) ||
						((currentRow == DIMENSIONS - 1) && (randomDirection.x == 1)) ||
						((currentColumn == DIMENSIONS - 1) && (randomDirection.y == 1))) {
						stop = true;
						break;
					}

					//Update the current position
					currentRow += randomDirection.x;
					currentColumn += randomDirection.y;

					tunnelLength++;
				}

				//When you cant go further stop
				if (breakIt == true) {
					break;
				}

				lastDiection = randomDirection;
			}
		}
	}

	//Some optimization
	for (int i = 1; i < DIMENSIONS - 1; i++) {
		for (int j = 1; j < DIMENSIONS - 1; j++) {
			if (numberOfNeighbours(i, j) == 1) {
				road[i][j] = 0;
			}
		}
	}

	//Filter for buildings
	for (int i = 1; i < DIMENSIONS - 1; i++) {
		for (int j = 1; j < DIMENSIONS - 1; j++) {
			if (road[i][j] == 0 && (getGreenNeighbours(i, j) >= 2 )) {
				road[i][j] = rand() % 2 + 2;
			}
		}
	}

	//Set intersections
	for (int i = 1; i < DIMENSIONS - 1; i++) {
		for (int j = 1; j < DIMENSIONS - 1; j++) {
			if (road[i][j] == 1) {
				type[i][j] = isIntersection(i, j);
			}
		}
	}

	type[0][0] = 2;
	type[0][DIMENSIONS - 1] = 2;
	type[DIMENSIONS - 1][0] = 2;
	type[DIMENSIONS - 1][DIMENSIONS - 1] = 2;
}

Road::~Road()
{
}

//Check the neighbours and tell if is an intersection or not
int Road::isIntersection(int i, int j) {
	
	int intersection = 0;

	if (road[i - 1][j] == 1){
		intersection++;
	}

	if (road[i][j - 1] == 1) {
		intersection++;
	}

	if (road[i + 1][j] == 1) {
		intersection++;
	}
	if (road[i][j - 1] == 1) {
		intersection++;
	}

	if (intersection > 2) {
		return 2;
	}

	if (road[i - 1][j] == 1 && road[i][j - 1] == 1) {
		return 2;
	}

	if (road[i - 1][j] == 1 && road[i][j + 1] == 1) {
		return 2;
	}

	if (road[i + 1][j] == 1 && road[i][j - 1] == 1) {
		return 2;
	}

	if (road[i + 1][j] == 1 && road[i][j + 1] == 1) {
		return 2;
	}
	//////////////////////////////////////////////////
	if (road[i - 1][j] == 1 && road[i + 1][j] == 1) {
		return 1;
	}

	return 0;
}

int Road::getType(int i, int j) {
	return type[i][j];
}

//Get green neighbouts for buildings
int Road::getGreenNeighbours(int row, int column) {

	int greenPoint = 0;

	/*for (int i = row - 1; i <= row + 1; i++) {
		for (int j = column - 1; j <= column + 1; j++) {
			if (i == row && j == column) {
			}
			else {
				if (road[i][j] == 0)
					greenPoint++;
			}
		}
	}*/


	if (road[row - 1][column] == 0) {
		greenPoint++;
	}

	if (road[row][column - 1] == 0) {
		greenPoint++;
	}

	if (road[row + 1][column] == 0) {
		greenPoint++;
	}

	if (road[row][column + 1] == 0) {
		greenPoint++;
	}

	return greenPoint;
}

//Check if you can start the road network from this point
bool Road::isAGreenPoint(int row, int column) {
	
	int greenPoint = 0;

	for (int i = row - 1; i <= row + 1; i++) {
		for (int j = column - 1; j <= column + 1; j++) {
			if (i == row && j == column) {
			}
			else {
				if (road[i][j] == 0)
					greenPoint++;
			}
		}
	}

	if (greenPoint == 8) {
		return true;
	}

	return false;
}

//Check the number of neighbours for optimization 
int Road::numberOfNeighbours(int currentRow, int currentColumn) {
	int neighbours = 0;

	if (road[currentRow - 1][currentColumn] == 1) {
		neighbours++;
	}

	if (road[currentRow + 1][currentColumn] == 1) {
		neighbours++;
	}

	if (road[currentRow][currentColumn + 1] == 1) {
		neighbours++;
	}

	if (road[currentRow][currentColumn - 1] == 1) {
		neighbours++;
	}

	return neighbours;
}

//This function ensures that the road is not doubled
//That is done by checking if a square of 4 pieces of road is going to form
bool Road::testNeighbours(glm::vec2 randomDirection, int currentRow, int currentColumn) {
	
	int r = currentRow + randomDirection.x;
	int c = currentColumn + randomDirection.y;

	if (r > 0 && r < DIMENSIONS && c > 0 && c < DIMENSIONS) {
		if (road[r][c - 1] == 1 && road[r - 1][c - 1] == 1 && road[r - 1][c] == 1) {
			return false;
		}

		if (road[r - 1][c] == 1 && road[r - 1][c + 1] == 1 && road[r][c + 1] == 1) {
			return false;
		}

		if (road[r][c + 1] == 1 && road[r + 1][c + 1] == 1 && road[r + 1][c] == 1) {
			return false;
		}

		if (road[r + 1][c] == 1 && road[r + 1][c - 1] == 1 && road[r][c - 1] == 1) {
			return false;
		}
	}

	return true;
}

void Road::setCoord(int i, int j, int value) {
	road[i][j] = value;
}

int Road::getCoord(int i, int j) {
	return road[i][j];
}

int Road::getSize() {
	return DIMENSIONS;
}
