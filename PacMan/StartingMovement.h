#pragma once
#include "Sprite.h"
#include "InputCommand.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include "AIPatterns.h"
#include <math.h>
class StartingMovement
{
public:
	StartingMovement();
	virtual void start(std::shared_ptr<Sprite> enemy, std::shared_ptr<AIPatterns> pattern, float deltaTime) = 0;
	virtual ~StartingMovement();
	int stage;
protected:
	std::shared_ptr<InputCommand> mm_command = nullptr;
};

class LeftPen : public StartingMovement
{
	virtual void start(std::shared_ptr<Sprite> enemy, std::shared_ptr<AIPatterns> pattern, float deltaTime);
	enum LEFT {
		CENTER,
		UP,
		DOWN
	};
	int stage = LEFT::UP;
};

class RightPen : public StartingMovement
{
	virtual void start(std::shared_ptr<Sprite> enemy, std::shared_ptr<AIPatterns> pattern, float deltaTime);
	enum RIGHT {
		CENTER,
		UP,
		DOWN
	};
	int stage = RIGHT::UP;
};

class CenterPen : public StartingMovement
{

};

class LeavePen : public StartingMovement
{
	virtual void start(std::shared_ptr<Sprite> enemy, std::shared_ptr<AIPatterns> pattern, float deltaTime);
	enum EXIT {
		CENTER,
		ALIGN,//go to the exact center
		UP
	};
	float alignDistance = 0;
	glm::vec2 penCenter = glm::vec2(13, 17);
	int stage = EXIT::UP;
};

