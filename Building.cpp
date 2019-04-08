#include "Building.h"


//Some radom values for buildings specifications
Building::Building(Road *road)
{
	for (int i = 0; i < DIMENSIONS; i++) {
		for (int j = 0; j < DIMENSIONS; j++) {
			if (road->getCoord(i, j) == 0) {
				levels[i][j] = rand() % 3 + 2;
				type[i][j] = rand() % 2;
				scale[i][j] = (rand() % 30 + 60.0f) / 100.0f;
			}
			if (road->getCoord(i, j) == 2) {
				scale[i][j] = rand() % 360;
			}
		}
	}

	for (int i = 0; i < DIMENSIONS; i++) {
		for (int j = 0; j < DIMENSIONS; j++) {
			if (road->getCoord(i, j) == 0) {
				if (type[i][j] == 0) {
					texture[i][j] = rand() % 6;
				}
				else {
					texture[i][j] = rand() % 3;
				}
			}
		}
	}
}

Building::~Building()
{
}

int Building::getLevel(int i, int j) { 
	return levels[i][j];
}

int Building::getType(int i, int j) {
	return type[i][j];
}

float Building::getScale(int i, int j) {
	return scale[i][j];
}

int Building::getTexture(int i, int j) {
	return texture[i][j];
}

void Building::generateBuilding() {
	
}
