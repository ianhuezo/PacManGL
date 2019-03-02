#include "Chase.h"

Chase::Chase()
{

}


Chase::~Chase()
{
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
		if (enemyAI->checkCurrent() == '+' || dispatcher.empty())
		{
			dispatcher = pattern->getMovementList();
		}
		m_command = dispatcher.front();
		dispatcher.pop_front();
	}
	m_command->execute(*enemyAI, 0.9*deltaTime);
}

void RandomChase::chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, std::shared_ptr<TileMap> map, float deltaTime)
{

}

void PatrolChase::chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, std::shared_ptr<TileMap> map, float deltaTime)
{
}

void AmbushChase::chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, std::shared_ptr<TileMap> map, float deltaTime)
{
	int y = static_cast<int>(pacman->getTileIndices().y);
	int x = static_cast<int>(pacman->getTileIndices().x);
	if (enemyAI->tileChanged == true || started == false)
	{
		started = true;
		if (abs(static_cast<int>(enemyAI->getTileIndices().x) - x) + abs(static_cast<int>(enemyAI->getTileIndices().y) - y) <= 3)
		{
			pattern->AStar(enemyAI->getTileIndices(), pacman->getTileIndices());
			m_blinkyMove = pattern->nextMovement;
			m_blinkyMove->execute(*enemyAI, deltaTime);
		}
		else
		{
			switch (pacman->spriteDirection)
			{
			case MOVE::LEFT:
				if (x < 28 && map->getChars()[y][x + 2] != '|' && map->getChars()[y + 2][x] != '0')
				{
					x += 2;
				}
				break;
			case MOVE::RIGHT:
				if (x >= 0 && map->getChars()[y][x - 2] != '|' && map->getChars()[y + 2][x] != '0')
				{
					x -= 2;
				}
				break;
			case MOVE::DOWN:
				if (y < 36 && map->getChars()[y + 2][x] != '|' && map->getChars()[y + 2][x] != '0')
				{
					y += 2;
				}
				break;
			case MOVE::UP:
				if (y >= 0 && map->getChars()[y - 2][x] != '|' && map->getChars()[y + 2][x] != '0')
				{
					y -= 2;
				}
				break;
			default:
				break;
			}
			pattern->AStar(enemyAI->getTileIndices(), glm::vec2(x, y));
			m_blinkyMove = pattern->nextMovement;
			m_blinkyMove->execute(*enemyAI, deltaTime);
		}
	}
	else {
		m_blinkyMove->execute(*enemyAI, deltaTime);
	}
}

void StopChase::chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, std::shared_ptr<TileMap> map, float deltaTime)
{
	std::make_shared<StillCommand>()->execute(*enemyAI, deltaTime);
}
