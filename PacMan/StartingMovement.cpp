#include "StartingMovement.h"



StartingMovement::StartingMovement()
{
}


StartingMovement::~StartingMovement()
{
}

void LeavePen::start(std::shared_ptr<Sprite> enemy, std::shared_ptr<AIPatterns> pattern, float deltaTime)
{
	enemy->setMoveMode(MODE::STARTING);
	switch (stage) {
		case EXIT::CENTER:
			if (enemy->getTileIndices() != penCenter)
			{
				pattern->AStar(enemy->getTileIndices(), penCenter, enemy->getPreviousPosition());
				mm_command = pattern->nextMovement;
			}
			else {
				stage = EXIT::UP;
			}
			break;
		case EXIT::UP:
			mm_command = std::make_shared<UpCommand>();
			break;
	}
	if (mm_command != nullptr)
	{
		mm_command->execute(*enemy, deltaTime);
	}
}

void LeftPen::start(std::shared_ptr<Sprite> enemy, std::shared_ptr<AIPatterns> pattern, float deltaTime)
{
	enemy->setMoveMode(MODE::STARTING);
	switch (stage)
	{
	case LEFT::CENTER:
		if (enemy->getTileIndices() != glm::vec2(12, 17))
		{
			pattern->AStar(enemy->getTileIndices(), glm::vec2(12, 17), glm::vec2(0, 0));
		}
		else {
			stage = LEFT::UP;
		}
		if (enemy->tileChanged)
		{
			mm_command = pattern->nextMovement;
		}
		if (mm_command != nullptr)
		{
			mm_command->execute(*enemy, deltaTime);
		}
		break;
	case LEFT::UP:
		if (enemy->getTileIndices() != glm::vec2(12, 16))
		{
			pattern->AStar(enemy->getTileIndices(), glm::vec2(12, 16), glm::vec2(0, 0));
		}
		else
		{
			stage = LEFT::DOWN;
		}
		mm_command = pattern->nextMovement;
		if (mm_command != nullptr)
		{
			mm_command->execute(*enemy, 0.9*deltaTime);
		}
		break;
	case LEFT::DOWN:
		if (enemy->getTileIndices() != glm::vec2(12, 18))
		{
			pattern->AStar(enemy->getTileIndices(), glm::vec2(12, 18), glm::vec2(0, 0));
		}
		else {
			stage = LEFT::UP;
		}
		mm_command = pattern->nextMovement;
		if (mm_command != nullptr)
		{
			mm_command->execute(*enemy, 0.9* deltaTime);
		}
		break;
	}
}

void RightPen::start(std::shared_ptr<Sprite> enemy, std::shared_ptr<AIPatterns> pattern, float deltaTime)
{
	enemy->setMoveMode(MODE::STARTING);
	switch (stage)
	{
	case RIGHT::CENTER:
		if (enemy->getTileIndices() != glm::vec2(16, 17))
		{
			pattern->AStar(enemy->getTileIndices(), glm::vec2(16, 17), glm::vec2(0, 0));
		}
		else {
			stage = RIGHT::UP;
		}
		if (enemy->tileChanged)
		{
			mm_command = pattern->nextMovement;
		}
		if (mm_command != nullptr)
		{
			mm_command->execute(*enemy, deltaTime);
		}
		break;
	case RIGHT::UP:
		if (enemy->getTileIndices() != glm::vec2(16, 16))
		{
			pattern->AStar(enemy->getTileIndices(), glm::vec2(16, 16), glm::vec2(0, 0));
		}
		else
		{
			stage = RIGHT::DOWN;
		}
		mm_command = pattern->nextMovement;
		if (mm_command != nullptr)
		{
			mm_command->execute(*enemy, deltaTime);
		}
		break;
	case RIGHT::DOWN:
		if (enemy->getTileIndices() != glm::vec2(16, 18))
		{
			pattern->AStar(enemy->getTileIndices(), glm::vec2(16, 18), glm::vec2(0, 0));
		}
		else {
			stage = RIGHT::UP;
		}
		mm_command = pattern->nextMovement;
		if (mm_command != nullptr)
		{
			mm_command->execute(*enemy, deltaTime);
		}
		break;
	}
}

void NoMovement::start(std::shared_ptr<Sprite> enemy, std::shared_ptr<AIPatterns> pattern, float deltaTime)
{
	enemy->setMoveMode(MODE::STARTING);
}
