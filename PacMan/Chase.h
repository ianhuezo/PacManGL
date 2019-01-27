#pragma once
#include "Sprite.h"
#include "InputCommand.h"
#include "TileMap.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

//chase classes inspired by https://dev.to/code2bits/pac-man-patterns--ghost-movement-strategy-pattern-1k1a/ this blogpost
class Chase
{
public:
	Chase();
	virtual std::shared_ptr<InputCommand> chase(Sprite& pacman, Sprite& enemyAI, TileMap& map) = 0;
	virtual ~Chase();
};

class AggresiveChase : public Chase
{
public:
	virtual std::shared_ptr<InputCommand> chase(Sprite& pacman, Sprite& enemyAI, TileMap& map);
};

class RandomChase : public Chase
{
public:
	virtual std::shared_ptr<InputCommand> chase(Sprite& pacman, Sprite& enemyAI, TileMap& map);
};

class PatrolChase : public Chase
{
public:
	virtual std::shared_ptr<InputCommand> chase(Sprite& pacman, Sprite& enemyAI, TileMap& map);
};

class AmbushChase : public Chase
{
public:
	virtual std::shared_ptr<InputCommand> chase(Sprite& pacman, Sprite& enemyAI, TileMap& map);
};


class EnemyHandler
{
public:
	EnemyHandler();
	std::shared_ptr<Chase> handleEnemyInput()
	{
		return enemyChase;
	}
private:
	std::shared_ptr<Chase> enemyChase;
};
