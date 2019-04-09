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
	std::cout << randomPosition(pacman, enemyAI, blinkysAI, map).x << std::endl;
	std::cout << randomPosition(pacman, enemyAI, blinkysAI, map).y << std::endl << std::endl;
}

glm::vec2 RandomChase::randomPosition(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<Sprite> blinkysAI, std::shared_ptr<TileMap> map)
{
	int dx = 0;
	int dy = 0;
	if (pacman->spriteDirection == MOVE::UP)
	{
		dy = pacman->getTileIndices().y - 2;
		dx = enemyAI->getTileIndices().x + 2 * (dx - enemyAI->getTileIndices().x);
		dy = enemyAI->getTileIndices().y + 2 * (dy - enemyAI->getTileIndices().y);
		//set bounds for inky
		if (dx < 1)
		{
			dx = 1;
		}
		if (dx > 24)
		{
			dx = 24;
		}
		if (dy < 4)
		{
			dy = 4;
		}
		if (dy > 32)
		{
			dy = 32;
		}
		while (!(map->getChars()[dy][dx] == '|' || map->getChars()[dy][dx] == '0'))
		{
			dy -= 1;
		}
		return glm::vec2(dx, dy);
	}
	else if (pacman->spriteDirection == MOVE::DOWN)
	{
		dy = pacman->getTileIndices().y + 2;
		dx = enemyAI->getTileIndices().x + 2 * (dx - enemyAI->getTileIndices().x);
		dy = enemyAI->getTileIndices().y + 2 * (dy - enemyAI->getTileIndices().y);
		//set bounds for inky
		if (dx < 1)
		{
			dx = 1;
		}
		if (dx > 24)
		{
			dx = 24;
		}
		if (dy < 4)
		{
			dy = 4;
		}
		if (dy > 32)
		{
			dy = 32;
		}
		while (!(map->getChars()[dy][dx] == '|' || map->getChars()[dy][dx] == '0'))
		{
			dy -= 1;
		}
		return glm::vec2(dx, dy);
	}
	else if (pacman->spriteDirection == MOVE::LEFT)
	{
		dx = pacman->getTileIndices().x - 2;
		dx = enemyAI->getTileIndices().x + 2 * (dx - enemyAI->getTileIndices().x);
		dy = enemyAI->getTileIndices().y + 2 * (dy - enemyAI->getTileIndices().y);
		//set bounds for inky
		if (dx < 1)
		{
			dx = 1;
		}
		if (dx > 24)
		{
			dx = 24;
		}
		if (dy < 4)
		{
			dy = 4;
		}
		if (dy > 32)
		{
			dy = 32;
		}
		while (!(map->getChars()[dy][dx] == '|' || map->getChars()[dy][dx] == '0'))
		{
			dx -= 1;
		}
		return glm::vec2(dx, dy);
	}
	else if (pacman->spriteDirection == MOVE::RIGHT)
	{
		dx = pacman->getTileIndices().x + 2;
		dx = enemyAI->getTileIndices().x + 2 * (dx - enemyAI->getTileIndices().x);
		dy = enemyAI->getTileIndices().y + 2 * (dy - enemyAI->getTileIndices().y);
		//set bounds for inky
		if (dx < 1)
		{
			dx = 1;
		}
		if (dx > 24)
		{
			dx = 24;
		}
		if (dy < 4)
		{
			dy = 4;
		}
		if (dy > 32)
		{
			dy = 32;
		}
		while (!(map->getChars()[dy][dx] == '|' || map->getChars()[dy][dx] == '0'))
		{
			dx += 1;
		}
		return glm::vec2(dx, dy);
	}

}

void PatrolChase::chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<Sprite> blinkysAI, std::shared_ptr<AIPatterns> pattern, std::shared_ptr<TileMap> map, float deltaTime)
{
	//A* algorithm that will "chase" pacman
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
