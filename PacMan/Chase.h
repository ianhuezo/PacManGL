#pragma once
#include "Sprite.h"
#include "InputCommand.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <iostream>
#include "TileMap.h"
#include "AIPatterns.h"
#include "SpriteDirection.h"
#include <math.h>
#include <iostream>
#include "WorldDispatcher.h"
#include <list>
#include <utility>
#include "SpriteDirection.h"
#include "Scatter.h"
#include <math.h>

//chase classes inspired by https://dev.to/code2bits/pac-man-patterns--ghost-movement-strategy-pattern-1k1a/ this blogpost

class Chase
{
public:
	Chase();
	virtual void chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<Sprite> blinkysAI,std::shared_ptr<AIPatterns> pattern, std::shared_ptr<TileMap> map, float deltaTime) = 0;
	virtual ~Chase();
protected:
	std::shared_ptr<InputCommand> mm_command;
};

class AggresiveChase : public Chase
{
public:
	virtual void chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<Sprite> blinkysAI, std::shared_ptr<AIPatterns> pattern, std::shared_ptr<TileMap> map, float deltaTime);
private:
};

class RandomChase : public Chase
{
public:
	virtual void chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<Sprite> blinkysAI, std::shared_ptr<AIPatterns> pattern, std::shared_ptr<TileMap> map, float deltaTime);
private:
	glm::vec2 randomPosition(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<Sprite> blinkysAI, std::shared_ptr<TileMap> map);
};

class PatrolChase : public Chase
{
public:
	virtual void chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<Sprite> blinkysAI, std::shared_ptr<AIPatterns> pattern, std::shared_ptr<TileMap> map, float deltaTime);
	std::shared_ptr<Scatter> m_clydeScatter = std::make_shared<BotLeftScatter>();
	void changeStage(std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, glm::vec2 destination, float deltaTime, int& stage, int nextStage);

	enum PATROLMODE {
		AGGRESSIVE,
		PATROL
	};
	int currentMode = PATROLMODE::AGGRESSIVE;

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

class AmbushChase : public Chase
{
public:
	virtual void chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<Sprite> blinkysAI, std::shared_ptr<AIPatterns> pattern, std::shared_ptr<TileMap> map, float deltaTime); private:
	//2 variables used to sense if pinky reached the 4 squares after pacman and if so, then follow pacman until the counter and revert
	//back to previous state for pinky
	int m_ambushCounter = 0;
	glm::vec2 ambushTile = glm::vec2(14, 26);
	bool m_ambushFlag = 0;
	glm::vec2 ambushPosition(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemy, std::shared_ptr<TileMap> map);
};

class StopChase : public Chase
{
public:
	virtual void chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<Sprite> blinkysAI, std::shared_ptr<AIPatterns> pattern, std::shared_ptr<TileMap> map, float deltaTime);
};
