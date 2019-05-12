#include "Frightened.h"



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
		mm_command = pattern->nextMovement;
	}

	mm_command->execute(*enemy, 0.5* deltaTime);
}

void BackToStart::fright(std::shared_ptr<Sprite> enemy, std::shared_ptr<AIPatterns> pattern, std::shared_ptr<TileMap> map, float deltaTime)
{
}

Frightened::~Frightened()
{
}
