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

//chase classes inspired by https://dev.to/code2bits/pac-man-patterns--ghost-movement-strategy-pattern-1k1a/ this blogpost

class Chase
{
public:
	Chase();
	virtual void chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, std::shared_ptr<TileMap> map , float deltaTime) = 0;
	virtual ~Chase();
};

class AggresiveChase : public Chase
{
public:
	virtual void chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, std::shared_ptr<TileMap> map, float deltaTime);
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
	std::shared_ptr<InputCommand> m_blinkyMove;
	bool started = false;
};

class StopChase : public Chase
{
public:
	virtual void chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern, std::shared_ptr<TileMap> map, float deltaTime);
};
