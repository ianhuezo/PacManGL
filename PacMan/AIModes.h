#pragma once
#include "Sprite.h"
#include "AIPatterns.h"
#include "Chase.h"
#include "Scatter.h"
#include "TileMap.h"
class AIModes
{
public:
	AIModes();
	virtual void AIMove(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<Sprite> blinkysAI, std::shared_ptr<AIPatterns> pattern, float deltaTime) = 0;
	~AIModes();
};

class ChaseMode : public AIModes
{
	virtual void AIMove(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<Sprite> blinkysAI, std::shared_ptr<AIPatterns> pattern, 
		std::shared_ptr<Chase> chaseType, std::shared_ptr<Scatter> ScatterType,float deltaTime) {
		enemyAI->moveAI()
	};
};

