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

//chase classes inspired by https://dev.to/code2bits/pac-man-patterns--ghost-movement-strategy-pattern-1k1a/ this blogpost

class Chase
{
public:
	Chase();
	virtual void chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, std::shared_ptr<TileMap> map, float deltaTime) = 0;
	virtual ~Chase();
protected:
	glm::vec2 mm_previousPosition = glm::vec2(0, 0);
	std::list<std::shared_ptr<InputCommand>> mm_dispatcher;
	std::shared_ptr<InputCommand> mm_command;
};

class AggresiveChase : public Chase
{
public:
	virtual void chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, std::shared_ptr<TileMap> map, float deltaTime);
private:
};

class RandomChase : public Chase
{
public:
	virtual void chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, std::shared_ptr<TileMap> map, float deltaTime);
};

class PatrolChase : public Chase
{
public:
	virtual void chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, std::shared_ptr<TileMap> map, float deltaTime);
};

class AmbushChase : public Chase
{
public:
	virtual void chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, std::shared_ptr<TileMap> map, float deltaTime);
private:
	//2 variables used to sense if pinky reached the 4 squares after pacman and if so, then follow pacman until the counter and revert
	//back to previous state for pinky
	int m_ambushCounter = 0;
	bool m_ambushFlag = 0;
	glm::vec2 ambushPosition(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemy, std::shared_ptr<TileMap> map);
	int prevHeuristic = 999999;
};

class StopChase : public Chase
{
public:
	virtual void chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, std::shared_ptr<TileMap> map, float deltaTime);
};
