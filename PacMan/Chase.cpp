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
	pattern->AStar(enemyAI->getTileIndices(), pacman->getTileIndices(), enemyAI->getPreviousPosition());
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
	glm::vec2 randomPos = randomPosition(pacman, enemyAI, blinkysAI, map);
	if (randomPos == enemyAI->getPreviousPosition())
	{
		pattern->AStar(enemyAI->getTileIndices(), pacman->getTileIndices(), enemyAI->getPreviousPosition());
	}
	else
	{
		pattern->AStar(enemyAI->getTileIndices(), randomPosition(pacman, enemyAI, blinkysAI, map), enemyAI->getPreviousPosition());
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
	if (result.y > 28)
	{
		result.y = 28;
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
	switch (currentMode)
	{
	case MODE::AGGRESSIVE:
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
				currentMode = MODE::PATROL;
			}
			mm_command = pattern->nextMovement;
		}
		mm_command->execute(*enemyAI, deltaTime);
		break;
	case MODE::PATROL:

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
				currentMode = MODE::AGGRESSIVE;
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
	pattern->AStar(enemyAI->getTileIndices(), ambushPosition(pacman, enemyAI, map) , enemyAI->getPreviousPosition());
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
	mm_command->execute(*enemyAI, deltaTime);
}

glm::vec2 AmbushChase::ambushPosition(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemy, std::shared_ptr<TileMap> map)
{
	int nextX = pacman->getTileIndices().x;
	int nextY = pacman->getTileIndices().y;

	//if statements go to 4 spaces from pacmans movement i.e. if up go 4 up from pacman
	//uses while loop to check for barriers and the pen to not interfere with A* algo
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

	if (!(enemy->getTileIndices().x == nextX && enemy->getTileIndices().y == nextY) && m_ambushFlag == 0)
	{
		return glm::vec2(nextX, nextY);
	}
	else
	{
		//set ambush flag to one and put a counter in to wait until ambush is set back
		m_ambushFlag = 1;
		m_ambushCounter++;
		if (m_ambushCounter > 4)
		{
			m_ambushFlag = 0;
			m_ambushCounter = 0;
		}
		return pacman->getTileIndices();
	}
}

void StopChase::chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<Sprite> blinkysAI, std::shared_ptr<AIPatterns> pattern, std::shared_ptr<TileMap> map, float deltaTime)
{
	std::make_shared<StillCommand>()->execute(*enemyAI, deltaTime);
}
