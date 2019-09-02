#include "Frightened.h"
#include <iostream>


void SlowFrightened::fright(std::shared_ptr<Sprite> enemy, std::shared_ptr<AIPatterns> pattern, std::shared_ptr<TileMap> map, float deltaTime)
{
	std::vector< glm::vec2> myvec = map->getValidPositions();
	do
	{
		std::random_shuffle(myvec.begin(), myvec.end());
	} while (*myvec.begin() == enemy->getTileIndices() || *myvec.begin() == enemy->getPreviousPosition());
	pattern->AStar(enemy->getTileIndices(), *myvec.begin() ,enemy->getPreviousPosition());
	if (enemy->tileChanged)
	{
		enemy->setPreviousPosition(enemy->getTileIndices());
		enemy->setMoveMode(MODE::FRIGHTENED);
		mm_command = pattern->nextMovement;
	}
	if (mm_command != nullptr) {
		mm_command->execute(*enemy, 0.5* deltaTime);
	}
}

void BackToStart::fright(std::shared_ptr<Sprite> enemy, std::shared_ptr<AIPatterns> pattern, std::shared_ptr<TileMap> map, float deltaTime)
{
	if (enemy->getTileIndices() != enemy->getInitialPosition())
	{
		pattern->AStar(enemy->getTileIndices(), enemy->getInitialPosition(), enemy->getPreviousPosition());
		enemy->setMoveMode(MODE::FRIGHTENED);
		if (enemy->tileChanged || mm_command == nullptr) {
			mm_command = pattern->nextMovement;
			enemy->setPreviousPosition(enemy->getTileIndices());
		}
		if (mm_command != nullptr) {
			mm_command->execute(*enemy, 4*deltaTime);
		}
	}
	else {
		pattern->AStar(enemy->getTileIndices(), enemy->getInitialPosition(), enemy->getPreviousPosition());
		enemy->setPreviousPosition(enemy->getTileIndices());
		enemy->setMoveMode(MODE::STARTING);
	}
}

Frightened::~Frightened()
{
}
