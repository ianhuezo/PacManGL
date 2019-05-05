#pragma once
#include "Chase.h"
#include "AIPatterns.h"
#include "Scatter.h"
#include "Sprite.h"
#include "PacManSprite.h"
#include "TileMap.h"
#include "EnemyMode.h"
#include <memory>
#include <string>
#include <map>
struct EnemyAI {
	std::shared_ptr<Sprite> sprite = nullptr;
	std::shared_ptr<Sprite> spriteDependency = nullptr;
	std::shared_ptr<AIPatterns> spriteAI = nullptr;
	std::shared_ptr<Chase> chaseMode = nullptr;
	std::shared_ptr<Scatter> scatterMode = nullptr;
};


class EnemyDispatcher
{
public:
	EnemyDispatcher(std::shared_ptr<AIPatterns> initialAI, std::shared_ptr<Sprite> blinky, std::shared_ptr<Sprite> inky, std::shared_ptr<Sprite> clyde, std::shared_ptr<Sprite> pinky,
		std::shared_ptr<TileMap> map);

	void targetHero(std::shared_ptr<Sprite> pacman, int enemyMode, float deltaTime);
	void collided(std::shared_ptr<Sprite> pacman);
	~EnemyDispatcher();
private:
	void initChase();
	void initScatter();
	void initAI(std::shared_ptr<AIPatterns> AIPattern);
	void useScatter(float deltaTime);
	void useChase(float deltaTime);
	void resetAI();
	void setAIModes(int globalAIMode);
	void decideMode(float deltaTime);


	int m_globalAIMode = -1;
	std::shared_ptr<TileMap> m_originalMap;
	//Pacman Sprite
	std::shared_ptr<Sprite> m_target;

	std::map<std::string, EnemyAI> m_enemies;
	//enemy sprites and their associated modes
	EnemyAI m_blinky;
	EnemyAI m_pinky;
	EnemyAI m_clyde;
	EnemyAI m_inky;

	//Pattern that all sprites default to for AI
	std::shared_ptr<AIPatterns> m_originalAI = nullptr;

};

