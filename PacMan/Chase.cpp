#include "Chase.h"

Chase::Chase()
{

}


Chase::~Chase()
{
}

void AggresiveChase::chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, float deltaTime)
{
	pattern->AStar(enemyAI->getTileIndices(), pacman->getTileIndices());
	pattern->nextMovement->execute(*enemyAI, deltaTime);
}

void RandomChase::chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, float deltaTime)
{
}

void PatrolChase::chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, float deltaTime)
{
}

void AmbushChase::chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, float deltaTime)
{
}
