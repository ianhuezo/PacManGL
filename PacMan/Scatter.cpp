#include "Scatter.h"

Scatter::Scatter()
{
}


Scatter::~Scatter()
{
}


//changeStage checks the stage each time and will either continue on it's path
//or go to the next stage
void Scatter::changeStage(std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, glm::vec2 destination, float deltaTime,int& stage, int nextStage)
{
	if (enemyAI->getTileIndices() != destination)
	{
		if (enemyAI->getMoveMode() != MODE::SCATTER && enemyAI->getPreviousPosition() != glm::vec2(0,0))
		{
			pattern->AStar(enemyAI->getTileIndices(), enemyAI->getPreviousPosition(), glm::vec2(0,0));
			enemyAI->setMoveMode(MODE::SCATTER);
		}
		else
		{
			pattern->AStar(enemyAI->getTileIndices(), destination, enemyAI->getPreviousPosition());
		}
		if (enemyAI->tileChanged)
		{
			enemyAI->setPreviousPosition(enemyAI->getTileIndices());
			enemyAI->setDistanceToPacman(pattern->getDistanceFromPacman());
			mm_command = pattern->nextMovement;
		}
		if (mm_command != nullptr)
		{
			mm_command->execute(*enemyAI, deltaTime);
		}
	}
	else {
		stage = nextStage;
	}
}

void StartingBlinkyScatter::scatter(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, float deltaTime)
{
	switch (stageNum)
	{
	case STAGE::INITIAL:
		changeStage(enemyAI, pattern, initial, deltaTime, stageNum, STAGE::UP);
		break;
	case STAGE::UP:
		changeStage(enemyAI, pattern, up, deltaTime, stageNum, STAGE::TOLOOP);
		break;
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


}

void TopRightScatter::scatter(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, float deltaTime)
{
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
}

void TopLeftScatter::scatter(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, float deltaTime)
{
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
}

void BotLeftScatter::scatter(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, float deltaTime)
{
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
}

void BotRightScatter::scatter(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, float deltaTime)
{
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
}
