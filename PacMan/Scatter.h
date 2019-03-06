#pragma once
#include "Sprite.h"
#include "memory"
#include "AIPatterns.h"
#include "InputCommand.h"

class Scatter
{
public:
	Scatter();
	virtual void scatter(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, float deltaTime) = 0;
	virtual ~Scatter();
protected:
	glm::vec2 previousPosition = glm::vec2(0, 0);
};

class TopRightScatter : public Scatter
{
public:
	virtual void scatter(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, float deltaTime);
private:
	enum STAGE {
		TOLOOP,
		LOOP1,
		LOOP2
	};
	int stageNum = STAGE::TOLOOP;
	glm::vec2 toLoop = glm::vec2(21, 8);
	glm::vec2 loop1 = glm::vec2(25, 4);
	glm::vec2 loop2 = glm::vec2(25, 8);
};

class TopLeftScatter : public Scatter
{
public:
	virtual void scatter(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, float deltaTime);
	enum STAGE {
		TOLOOP,
		LOOP1,
		LOOP2
	};
	int stageNum = STAGE::TOLOOP;
	glm::vec2 toLoop = glm::vec2(6, 8);
	glm::vec2 loop1 = glm::vec2(2, 4);
	glm::vec2 loop2 = glm::vec2(1, 8);
};

class BotLeftScatter : public Scatter
{
public:
	virtual void scatter(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, float deltaTime);
	enum STAGE {
		TOLOOP,
		LOOP1,
		LOOP2
	};
	int stageNum = STAGE::TOLOOP;
	glm::vec2 toLoop = glm::vec2(6, 26);
	glm::vec2 loop1 = glm::vec2(6, 32);
	glm::vec2 loop2 = glm::vec2(7, 32);
};

class BotRightScatter : public Scatter
{
public:
	virtual void scatter(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, float deltaTime);
	enum STAGE {
		TOLOOP,
		LOOP1,
		LOOP2
	};
	int stageNum = STAGE::TOLOOP;
	glm::vec2 toLoop = glm::vec2(18, 26);
	glm::vec2 loop1 = glm::vec2(26, 32);
	glm::vec2 loop2 = glm::vec2(22, 32);
};

class StartingBlinkyScatter : public Scatter
{
public:
	virtual void scatter(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, float deltaTime);
private:
	enum STAGE {
		INITIAL,
		UP,
		TOLOOP,
		LOOP1,
		LOOP2
	};
	int stageNum = STAGE::INITIAL;
	glm::vec2 initial = glm::vec2(6, 17);
	glm::vec2 up = glm::vec2(6, 8);
	glm::vec2 toLoop = glm::vec2(21, 8);
	glm::vec2 loop1 = glm::vec2(25, 4);
	glm::vec2 loop2 = glm::vec2(25, 8);
};
