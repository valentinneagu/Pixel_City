#pragma once

#include <stdlib.h>
#include <Core/Engine.h>
#include "Road.h"

#define DIMENSIONS 50

class Building
{
public:
	Building(Road *road);
	~Building();

	void generateBuilding();
	int getLevel(int i, int j);
	int getType(int i, int j);
	float getScale(int i, int j);
	int getTexture(int i, int j);
	
private:
	int levels[DIMENSIONS][DIMENSIONS];
	int type[DIMENSIONS][DIMENSIONS];
	float scale[DIMENSIONS][DIMENSIONS];
	int texture[DIMENSIONS][DIMENSIONS];
};

