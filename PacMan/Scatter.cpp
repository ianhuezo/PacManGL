#include "Scatter.h"

Scatter::Scatter()
{
}


Scatter::~Scatter()
{
}

void StartingBlinkyScatter::scatter(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, float deltaTime)
{
	switch (stageNum)
	{
	case STAGE::INITIAL:
		if (enemyAI->getTileIndices() != initial)
		{
			pattern->AStar(enemyAI->getTileIndices(), initial, previousPosition);
			pattern->nextMovement->execute(*enemyAI, deltaTime);
		}
		else {
			stageNum = STAGE::UP;
		}
		break;
	case STAGE::UP:
		if (enemyAI->getTileIndices() != up)
		{
			pattern->AStar(enemyAI->getTileIndices(), up, previousPosition);
			pattern->nextMovement->execute(*enemyAI, deltaTime);
		}
		else {
			stageNum = STAGE::TOLOOP;
		}
		break;
	case STAGE::TOLOOP:
		if (enemyAI->getTileIndices() != toLoop)
		{
			pattern->AStar(enemyAI->getTileIndices(), toLoop, previousPosition);
			pattern->nextMovement->execute(*enemyAI, deltaTime);
		}
		else {
			stageNum = STAGE::LOOP1;
		}
		break;
	case STAGE::LOOP1:
		if (enemyAI->getTileIndices() != loop1)
		{
			pattern->AStar(enemyAI->getTileIndices(), loop1, previousPosition);
			pattern->nextMovement->execute(*enemyAI, deltaTime);
		}
		else {
			stageNum = STAGE::LOOP2;
		}
		break;
	case STAGE::LOOP2:
		if (enemyAI->getTileIndices() != loop2)
		{
			pattern->AStar(enemyAI->getTileIndices(), loop2, previousPosition);
			pattern->nextMovement->execute(*enemyAI, deltaTime);
		}
		else {
			stageNum = STAGE::TOLOOP;
		}
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
		if (enemyAI->getTileIndices() != toLoop)
		{
			pattern->AStar(enemyAI->getTileIndices(), toLoop, previousPosition);
			pattern->nextMovement->execute(*enemyAI, deltaTime);
		}
		else {
			stageNum = STAGE::LOOP1;
		}
		break;
	case STAGE::LOOP1:
		if (enemyAI->getTileIndices() != loop1)
		{
			pattern->AStar(enemyAI->getTileIndices(), loop1, previousPosition);
			pattern->nextMovement->execute(*enemyAI, deltaTime);
		}
		else {
			stageNum = STAGE::LOOP2;
		}
		break;
	case STAGE::LOOP2:
		if (enemyAI->getTileIndices() != loop2)
		{
			pattern->AStar(enemyAI->getTileIndices(), loop2, previousPosition);
			pattern->nextMovement->execute(*enemyAI, deltaTime);
		}
		else {
			stageNum = STAGE::TOLOOP;
		}
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
		if (enemyAI->getTileIndices() != toLoop)
		{
			pattern->AStar(enemyAI->getTileIndices(), toLoop, previousPosition);
			pattern->nextMovement->execute(*enemyAI, deltaTime);
		}
		else {
			stageNum = STAGE::LOOP1;
		}
		break;
	case STAGE::LOOP1:
		if (enemyAI->getTileIndices() != loop1)
		{
			pattern->AStar(enemyAI->getTileIndices(), loop1, previousPosition);
			pattern->nextMovement->execute(*enemyAI, deltaTime);
		}
		else {
			stageNum = STAGE::LOOP2;
		}
		break;
	case STAGE::LOOP2:
		if (enemyAI->getTileIndices() != loop2)
		{
			pattern->AStar(enemyAI->getTileIndices(), loop2, previousPosition);
			pattern->nextMovement->execute(*enemyAI, deltaTime);
		}
		else {
			stageNum = STAGE::TOLOOP;
		}
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
		if (enemyAI->getTileIndices() != toLoop)
		{
			pattern->AStar(enemyAI->getTileIndices(), toLoop, previousPosition);
			pattern->nextMovement->execute(*enemyAI, deltaTime);
		}
		else {
			stageNum = STAGE::LOOP1;
		}
		break;
	case STAGE::LOOP1:
		if (enemyAI->getTileIndices() != loop1)
		{
			pattern->AStar(enemyAI->getTileIndices(), loop1, previousPosition);
			pattern->nextMovement->execute(*enemyAI, deltaTime);
		}
		else {
			stageNum = STAGE::LOOP2;
		}
		break;
	case STAGE::LOOP2:
		if (enemyAI->getTileIndices() != loop2)
		{
			pattern->AStar(enemyAI->getTileIndices(), loop2, previousPosition);
			pattern->nextMovement->execute(*enemyAI, deltaTime);
		}
		else {
			stageNum = STAGE::TOLOOP;
		}
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
		if (enemyAI->getTileIndices() != toLoop)
		{
			pattern->AStar(enemyAI->getTileIndices(), toLoop, previousPosition);
			pattern->nextMovement->execute(*enemyAI, deltaTime);
		}
		else {
			stageNum = STAGE::LOOP1;
		}
		break;
	case STAGE::LOOP1:
		if (enemyAI->getTileIndices() != loop1)
		{
			pattern->AStar(enemyAI->getTileIndices(), loop1, previousPosition);
			pattern->nextMovement->execute(*enemyAI, deltaTime);
		}
		else {
			stageNum = STAGE::LOOP2;
		}
		break;
	case STAGE::LOOP2:
		if (enemyAI->getTileIndices() != loop2)
		{
			pattern->AStar(enemyAI->getTileIndices(), loop2, previousPosition);
			pattern->nextMovement->execute(*enemyAI, deltaTime);
		}
		else {
			stageNum = STAGE::TOLOOP;
		}
		break;
	default:
		break;
	}
}
