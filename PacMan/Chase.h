#pragma once
#include "Sprite.h"
#include "InputCommand.h"
#include "TileMap.h"
#include <memory>

//chase classes inspired by https://dev.to/code2bits/pac-man-patterns--ghost-movement-strategy-pattern-1k1a/ this blogpost
class Chase
{
public:
	Chase();
	virtual InputCommand* chase(Sprite& pacman, Sprite& enemyAI, TileMap& map);
	virtual ~Chase();
};

class AggresiveChase : Chase
{
public:
	virtual InputCommand* chase(Sprite& pacman, Sprite& enemyAI, TileMap& map);
};

class RandomChase : Chase
{
public:
	virtual InputCommand* chase(Sprite& pacman, Sprite& enemyAI, TileMap& map);
};

class PatrolChase : Chase
{
public:
	virtual InputCommand* chase(Sprite& pacman, Sprite& enemyAI, TileMap& map);
};

class AmbushChase : Chase
{
public:
	virtual InputCommand* chase(Sprite& pacman, Sprite& enemyAI, TileMap& map);
};
