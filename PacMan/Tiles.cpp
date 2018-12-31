#include "stdafx.h"
#include "Tiles.h"


void FruitTile::assignRandomFruit()
{
	int randNum = rand() % (8) + 0;
	FRUIT allFruits[] = { CHERRY,STRAWBERRY,ORANGE, KEY,
						 MELON, BOSS, KEY, BELL };
	m_randFruit = static_cast<int>(allFruits[randNum]);
}

Tiles::Tiles()
{
}
