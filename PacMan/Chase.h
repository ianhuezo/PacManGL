#pragma once
#include "Sprite.h"
#include "InputCommand.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <iostream>
#include <map>
#include "AIPatterns.h"

//chase classes inspired by https://dev.to/code2bits/pac-man-patterns--ghost-movement-strategy-pattern-1k1a/ this blogpost

class Chase
{
public:
	Chase();
	bool startedChase = true;
	bool isFinished = false;
	//void AStar(Node start, Node goal, std::shared_ptr<AIPatterns> pattern);
	//std::list<Node> findNeighbors(Node current, TileMap & map);
	//int calculateHeuristic(Node& start, Node& goal);
	std::shared_ptr<InputCommand> currentCommand;
	virtual std::shared_ptr<InputCommand> chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern) = 0;
	virtual ~Chase();
};

class AggresiveChase : public Chase
{
public:
	virtual std::shared_ptr<InputCommand> chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern);
};

class RandomChase : public Chase
{
public:
	virtual std::shared_ptr<InputCommand> chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern);
};

class PatrolChase : public Chase
{
public:
	virtual std::shared_ptr<InputCommand> chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern);
};

class AmbushChase : public Chase
{
public:
	virtual std::shared_ptr<InputCommand> chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern);
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
