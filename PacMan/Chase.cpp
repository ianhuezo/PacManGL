#include "Chase.h"

Chase::Chase()
{

}


Chase::~Chase()
{
}

bool Chase::isReversed(int spriteState1, int spriteState2)
{
	if (spriteState1 == MOVE::UP && spriteState2 == MOVE::DOWN)
	{
		return true;
	}
	else if (spriteState1 == MOVE::DOWN && spriteState2 == MOVE::UP)
	{
		return true;
	}
	else if (spriteState1 == MOVE::LEFT && spriteState2 == MOVE::RIGHT)
	{
		return true;
	}
	else if (spriteState1 == MOVE::RIGHT && spriteState2 == MOVE::LEFT)
	{
		return true;
	}
	return false;
}

void AggresiveChase::chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, std::shared_ptr<TileMap> map, float deltaTime)
{
	//this astar searches for a minigoal to pacman, so, they dont immediately go to pacman but rather the minigoal if there is one

	////////////////////////Part where AI acts like a player, making decisions and inputting a command
	pattern->AStar(pacman->getTileIndices(), enemyAI->getTileIndices());
	if (pattern->atGoal())
	{
		return;
	}
	if (enemyAI->tileChanged)
	{
		if (mm_dispatcher.empty())
		{
			mm_dispatcher = pattern->getMovementList();
		}
		else if (enemyAI->checkCurrent() == '+' && isReversed(enemyAI->spriteDirection, mm_dispatcher.front()->spriteState))
		{
			mm_dispatcher = pattern->getMovementList();
		}
		mm_command = mm_dispatcher.front();
		mm_dispatcher.pop_front();
	}
	mm_command->execute(*enemyAI, deltaTime);
}

void RandomChase::chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, std::shared_ptr<TileMap> map, float deltaTime)
{

}

void PatrolChase::chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, std::shared_ptr<TileMap> map, float deltaTime)
{

}

void AmbushChase::chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, std::shared_ptr<TileMap> map, float deltaTime)
{
	pattern->AStar(ambushPosition(pacman,map), enemyAI->getTileIndices());
	if (pattern->atGoal())
	{
		return;
	}
	if (enemyAI->tileChanged)
	{
		if (mm_dispatcher.empty())
		{
			mm_dispatcher = pattern->getMovementList();
		}
		else if (enemyAI->checkCurrent() == '+' && isReversed(enemyAI->spriteDirection, mm_dispatcher.front()->spriteState))
		{
			mm_dispatcher = pattern->getMovementList();
		}
		mm_command = mm_dispatcher.front();
		mm_dispatcher.pop_front();
	}
	mm_command->execute(*enemyAI, deltaTime);
}

glm::vec2 AmbushChase::ambushPosition(std::shared_ptr<Sprite> pacman, std::shared_ptr<TileMap> map)
{
	int posx = static_cast<int>(pacman->getTileIndices().x);
	int posy = static_cast<int>(pacman->getTileIndices().y);
	int nextX = posx;
	int nextY = posy;

	if (pacman->spriteDirection == MOVE::UP)
	{
		nextY -= 4;
		while (nextY <= 4 || (map->getChars()[nextY][nextX] == '|' || map->getChars()[nextY][nextX] == '0'))
		{
			nextY++;
		}
	}
	else if (pacman->spriteDirection == MOVE::DOWN)
	{
		nextY += 4;
		while (nextY >= 34 || map->getChars()[nextY][nextX] == '|' || map->getChars()[nextY][nextX] == 'p')
		{
			nextY--;
		}
	}
	else if (pacman->spriteDirection == MOVE::LEFT)
	{
		nextX -= 4;
		while (nextX < 0 || map->getChars()[nextY][nextX] == '|' || map->getChars()[nextY][nextX] == 'p')
		{
			nextX++;
		}
	}
	else if (pacman->spriteDirection == MOVE::RIGHT)
	{
		nextX += 4;
		while (nextX > 24 || map->getChars()[nextY][nextX] == '|' || map->getChars()[nextY][nextX] == 'p')
		{
			nextX--;
		}
	}

	
	return glm::vec2(nextX, nextY);
}

void StopChase::chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, std::shared_ptr<TileMap> map, float deltaTime)
{
	std::make_shared<StillCommand>()->execute(*enemyAI, deltaTime);
}
