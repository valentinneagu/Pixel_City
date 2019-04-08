#pragma once

#include <stdlib.h>
#include <Core/Engine.h>

#define DIMENSIONS 50
#define MaxTUNNELS 1
#define MaxLENGTH 10
#define INTENSITY 20
#define MINIMUM_GREEN_POINTS 5

class Road
{
	public:
		Road();
		~Road();

		void setCoord(int i, int j, int value);
		int getCoord(int i, int j);
		int getSize();
		bool testNeighbours(glm::vec2 randomDirection, int currentRow, int currentColumn);
		int numberOfNeighbours(int currentRow, int currentColumn);
		bool isAGreenPoint(int row, int column);
		int getGreenNeighbours(int row, int column);
		int isIntersection(int i, int j);
		int getType(int i, int j);
	private:
		int road[DIMENSIONS][DIMENSIONS];
		int type[DIMENSIONS][DIMENSIONS];
		std::vector<glm::vec2> directions = { glm::vec2(-1, 0),
										 glm::vec2(1, 0),
										 glm::vec2(0, -1),
										 glm::vec2(0, 1) };
};

