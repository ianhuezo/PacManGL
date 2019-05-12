#pragma once
#include "Sprite.h"
#include "TileMap.h"
#include "AIPatterns.h"
#include <memory>
#include <algorithm>
#include "InputCommand.h"
#include <vector>

class Frightened
{
public:
	virtual void fright(std::shared_ptr<Sprite> enemy, std::shared_ptr<AIPatterns> pattern,std::shared_ptr<TileMap> map, float deltaTime) = 0;
	virtual ~Frightened();

protected:
	std::shared_ptr<InputCommand> mm_command = nullptr;

};

class BackToStart: public Frightened
{
public:
	virtual void fright(std::shared_ptr<Sprite> enemy, std::shared_ptr<AIPatterns> pattern, std::shared_ptr<TileMap> map, float deltaTime);
};

class SlowFrightened : public Frightened
{
public:
	virtual void fright(std::shared_ptr<Sprite> enemy, std::shared_ptr<AIPatterns> pattern, std::shared_ptr<TileMap> map, float deltaTime);
};