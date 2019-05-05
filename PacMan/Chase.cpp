#include "Chase.h"


////////////////////////Part where AI acts like a player, making decisions and inputting a command
Chase::Chase()
{

}


Chase::~Chase()
{
}


void AggresiveChase::chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<Sprite> blinkysAI, std::shared_ptr<AIPatterns> pattern, std::shared_ptr<TileMap> map, float deltaTime)
{
	//A* algorithm that will "chase" pacman
	if (enemyAI->inTunnel())
	{
		mm_command->execute(*enemyAI, deltaTime);
		return;
	}
	if (enemyAI->getMoveMode() != MODE::CHASE && enemyAI->getPreviousPosition() != glm::vec2(0, 0))
	{
		pattern->AStar(enemyAI->getTileIndices(), enemyAI->getPreviousPosition(), glm::vec2(0,0));
		enemyAI->setMoveMode(MODE::CHASE);
	}
	else
	{
		pattern->AStar(enemyAI->getTileIndices(), pacman->getTileIndices(), enemyAI->getPreviousPosition());
	}
	if (pattern->atGoal())
	{
		return;
	}
	//prevents enemies from going out of bounds onto the blue tiles
	if (enemyAI->tileChanged)
	{
		enemyAI->setPreviousPosition(enemyAI->getTileIndices());
		mm_command = pattern->nextMovement;
	}
	mm_command->execute(*enemyAI, deltaTime);
}

void RandomChase::chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<Sprite> blinkysAI, std::shared_ptr<AIPatterns> pattern, std::shared_ptr<TileMap> map, float deltaTime)
{
	//A* algorithm that will "chase" pacman
	if (enemyAI->inTunnel())
	{
		mm_command->execute(*enemyAI, deltaTime);
		return;
	}
	if (enemyAI->getMoveMode() != MODE::CHASE && enemyAI->getPreviousPosition() != glm::vec2(0, 0))
	{
		pattern->AStar(enemyAI->getTileIndices(), enemyAI->getPreviousPosition(), glm::vec2(0, 0));
		enemyAI->setMoveMode(MODE::CHASE);
	}
	else
	{
		glm::vec2 randomPos = randomPosition(pacman, enemyAI, blinkysAI, map);
		if (randomPos == enemyAI->getPreviousPosition())
		{
			pattern->AStar(enemyAI->getTileIndices(), pacman->getTileIndices(), enemyAI->getPreviousPosition());
		}
		else
		{
			pattern->AStar(enemyAI->getTileIndices(), randomPosition(pacman, enemyAI, blinkysAI, map), enemyAI->getPreviousPosition());
		}
	}
	if (pattern->atGoal())
	{
		return;
	}
	//prevents enemies from going out of bounds onto the blue tiles
	if (enemyAI->tileChanged)
	{
		enemyAI->setPreviousPosition(enemyAI->getTileIndices());
		mm_command = pattern->nextMovement;
	}
	if (mm_command != nullptr)
	{
		mm_command->execute(*enemyAI, deltaTime);
	}
}

glm::vec2 RandomChase::randomPosition(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<Sprite> blinkysAI, std::shared_ptr<TileMap> map)
{
	glm::vec2 result = glm::vec2(pacman->getTileIndices().x, pacman->getTileIndices().y);
	bool highX = false;
	bool lowX = false;
	if (pacman->spriteDirection == MOVE::UP)
	{
		result.y -= 2;
		result += 2.0f * (result - blinkysAI->getTileIndices());
	}
	else if (pacman->spriteDirection == MOVE::DOWN)
	{
		result.y += 2;
		result += 2.0f * (result - blinkysAI->getTileIndices());
	}
	else if (pacman->spriteDirection == MOVE::LEFT)
	{
		result.x += 2;
		result += 2.0f * (result - blinkysAI->getTileIndices());
	}
	else if (pacman->spriteDirection == MOVE::RIGHT)
	{
		result.x += 2;
		result += 2.0f * (result - blinkysAI->getTileIndices());
	}
	if (result.y > 27)
	{
		result.y = 27;
	}
	else if (result.y < 4)
	{
		result.y = 4;
	}
	if (result.x < 0)
	{
		result.x = 0;
		lowX = true;
	}
	else if (result.x > 24)
	{
		result.x = 24;
		highX = true;
	}
	while (
		result.x < 0 ||
		result.x > 24 ||
		pacman->getPreviousPosition() == result || 
		map->getChars()[static_cast<int>(result.y)][static_cast<int>(result.x)] == '|' ||
		map->getChars()[static_cast<int>(result.y)][static_cast<int>(result.x)] == 'p' ||
		map->getChars()[static_cast<int>(result.y)][static_cast<int>(result.x)] == 'g')
	{
		if (highX)
		{
			result.x -= 1;
		}
		else if (lowX)
		{
			result.x += 1;
		}
		else if (result.x > 24)
		{
			highX = true;
			lowX = false;
		}
		else if (result.x < 0)
		{
			lowX = true;
			highX = false;
		}
		else {
			result.x -= 1;
		}
	}
	if (enemyAI->getTileIndices() == result || pacman->getTileIndices() == enemyAI->getPreviousPosition())
	{
		result = pacman->getTileIndices();
	}
	
	return result;

	

}

void PatrolChase::chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<Sprite> blinkysAI, std::shared_ptr<AIPatterns> pattern, std::shared_ptr<TileMap> map, float deltaTime)
{
	//A* algorithm that will "chase" pacman
	if (enemyAI->inTunnel())
	{
		mm_command->execute(*enemyAI, deltaTime);
		return;
	}
	if (enemyAI->getMoveMode() != MODE::CHASE && enemyAI->getPreviousPosition() != glm::vec2(0, 0))
	{
		pattern->AStar(enemyAI->getTileIndices(), enemyAI->getPreviousPosition(), glm::vec2(0, 0));
		enemyAI->setMoveMode(MODE::CHASE);
	}
	else
	{
		switch (currentMode)
		{
		case PATROLMODE::AGGRESSIVE:
			pattern->AStar(enemyAI->getTileIndices(), pacman->getTileIndices(), enemyAI->getPreviousPosition());
			if (pattern->atGoal())
			{
				return;
			}
			//prevents enemies from going out of bounds onto the blue tiles
			if (enemyAI->tileChanged)
			{
				enemyAI->setPreviousPosition(enemyAI->getTileIndices());
				enemyAI->setDistanceToPacman(pattern->getDistanceFromPacman());
				if (enemyAI->getDistanceToPacman() < 8)
				{
					currentMode = PATROLMODE::PATROL;
				}
				mm_command = pattern->nextMovement;
			}
			mm_command->execute(*enemyAI, deltaTime);
			break;
		case PATROLMODE::PATROL:

			switch (stageNum)
			{
			case STAGE::TOLOOP:
				changeStage(enemyAI, pattern, toLoop, deltaTime, stageNum, STAGE::LOOP1);
				break;
			case STAGE::LOOP1:
				changeStage(enemyAI, pattern, loop1, deltaTime, stageNum, STAGE::LOOP2);
				break;
			case STAGE::LOOP2:
				changeStage(enemyAI, pattern, loop2, deltaTime, stageNum, STAGE::TOLOOP);
				break;
			default:
				break;
			}
			break;
		}
	}
}

void PatrolChase::changeStage(std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, glm::vec2 destination, float deltaTime, int & stage, int nextStage)
{
	if (enemyAI->getTileIndices() != destination)
	{
		pattern->AStar(enemyAI->getTileIndices(), destination, enemyAI->getPreviousPosition());
		if (enemyAI->tileChanged)
		{
			enemyAI->setPreviousPosition(enemyAI->getTileIndices());
			enemyAI->setDistanceToPacman(pattern->getDistanceFromPacman());
			if (enemyAI->getDistanceToPacman() < 8)
			{
				currentMode = PATROLMODE::AGGRESSIVE;
			}
			mm_command = pattern->nextMovement;
		}
		mm_command->execute(*enemyAI, deltaTime);
	}
	else {
		stage = nextStage;
	}
}

void AmbushChase::chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<Sprite> blinkysAI, std::shared_ptr<AIPatterns> pattern, std::shared_ptr<TileMap> map, float deltaTime)
{
	//An always running A* algo that the sprite uses to move
	//prevention of moving backwards by feeding in the previous position for the sprite
	if (enemyAI->inTunnel())
	{
		mm_command->execute(*enemyAI, deltaTime);
		return;
	}

	glm::vec2 amPosition = ambushPosition(pacman, enemyAI, map);

	if (amPosition == enemyAI->getPreviousPosition())
	{
		pattern->AStar(enemyAI->getTileIndices(), pacman->getTileIndices(), enemyAI->getPreviousPosition());
	}
	else
	{
		pattern->AStar(enemyAI->getTileIndices(), amPosition, enemyAI->getPreviousPosition());
	}

	if (pattern->atGoal())
	{
		return;
	}
	//prevents enemies from going out of bounds onto the blue tiles
	//and keeps track of the previous positions of the enemy
	if (enemyAI->tileChanged)
	{
		enemyAI->setPreviousPosition(enemyAI->getTileIndices());
		mm_command = pattern->nextMovement;
	}
	if (mm_command != nullptr)
	{
		mm_command->execute(*enemyAI, deltaTime);
	}
}

glm::vec2 AmbushChase::ambushPosition(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemy, std::shared_ptr<TileMap> map)
{
	int nextX = pacman->getTileIndices().x;
	int nextY = pacman->getTileIndices().y;
	bool highX = false;
	bool lowX = false;

	//if statements go to 4 spaces from pacmans movement i.e. if up go 4 up from pacman
	//uses while loop to check for barriers and the pen to not interfere with A* algo
	if (pacman->spriteDirection == MOVE::UP)
	{
		nextY -= 4;
	}
	else if (pacman->spriteDirection == MOVE::DOWN)
	{
		nextY += 4;
	}
	else if (pacman->spriteDirection == MOVE::LEFT)
	{
		nextX -= 4;
	}
	else if (pacman->spriteDirection == MOVE::RIGHT)
	{
		nextX += 4;
	}
	if (nextY < 4)
	{
		nextY = 4;
	}
	else if (nextY > 27)
	{
		nextY = 27;
	}
	if (nextX < 0)
	{
		nextX = 0;
	}
	else if (nextX > 24)
	{
		nextX = 24;
	}
	glm::vec2 result = glm::vec2(nextX, nextY);
	while (
		result.x < 0 ||
		result.x > 24 ||
		pacman->getPreviousPosition() == result ||
		map->getChars()[static_cast<int>(result.y)][static_cast<int>(result.x)] == '|' ||
		map->getChars()[static_cast<int>(result.y)][static_cast<int>(result.x)] == 'p' ||
		map->getChars()[static_cast<int>(result.y)][static_cast<int>(result.x)] == 'g')
	{
		if (highX)
		{
			result.x -= 1;
		}
		else if (lowX)
		{
			result.x += 1;
		}
		else if (result.x > 24)
		{
			highX = true;
			lowX = false;
		}
		else if (result.x < 0)
		{
			lowX = true;
			highX = false;
		}
		else {
			result.x -= 1;
		}
	}
	if (enemy->getTileIndices() == result || pacman->getTileIndices() == enemy->getPreviousPosition())
	{
		result = pacman->getTileIndices();
	}

	return result;
}

void StopChase::chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<Sprite> blinkysAI, std::shared_ptr<AIPatterns> pattern, std::shared_ptr<TileMap> map, float deltaTime)
{
	std::make_shared<StillCommand>()->execute(*enemyAI, deltaTime);
}
