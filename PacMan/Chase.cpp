#include "Chase.h"



Chase::Chase()
{
}

InputCommand * Chase::chase(Sprite & pacman, Sprite & enemyAI, TileMap & map)
{
	return nullptr;
}

Chase::~Chase()
{
}

InputCommand * AggresiveChase::chase(Sprite & pacman, Sprite & enemyAI, TileMap & map)
{
	return nullptr;
}

InputCommand * RandomChase::chase(Sprite & pacman, Sprite & enemyAI, TileMap & map)
{
	return nullptr;
}

InputCommand * PatrolChase::chase(Sprite & pacman, Sprite & enemyAI, TileMap & map)
{
	return nullptr;
}

InputCommand * AmbushChase::chase(Sprite & pacman, Sprite & enemyAI, TileMap & map)
{
	return nullptr;
}
