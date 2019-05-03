#pragma once
#include "Chase.h"
#include "AIPatterns.h"
#include "Scatter.h"
#include "Sprite.h"
#include "PacManSprite.h"
#include "TileMap.h"
#include "EnemyMode.h"
#include <memory>

class EnemyDispatcher
{
public:
	EnemyDispatcher(std::shared_ptr<AIPatterns> initialAI, std::shared_ptr<Sprite> blinky, std::shared_ptr<Sprite> inky, std::shared_ptr<Sprite> clyde, std::shared_ptr<Sprite> pinky,
		std::shared_ptr<TileMap> map);

	void targetHero(std::shared_ptr<Sprite> pacman, int enemyMode, float deltaTime);
	~EnemyDispatcher();
private:
	void initChase();
	void initScatter();
	void initAI(std::shared_ptr<AIPatterns> AIPattern);
	void useScatter(float deltaTime);
	void useChase(float deltaTime);
	void resetAI();



	std::shared_ptr<TileMap> m_originalMap;
	//Pacman Sprite
	std::shared_ptr<Sprite> m_target;


	//enemy sprites
	std::shared_ptr<Sprite> m_blinky;
	std::shared_ptr<Sprite> m_pinky;
	std::shared_ptr<Sprite> m_clyde;
	std::shared_ptr<Sprite> m_inky;

	//Pattern that all sprites default to for AI
	std::shared_ptr<AIPatterns> m_originalAI = nullptr;

	//AI Patterns for blinky
	std::shared_ptr<AIPatterns> m_blinkyAIPatterns = nullptr;
	std::shared_ptr<Chase> m_blinkyChase = nullptr;
	std::shared_ptr<Scatter> m_blinkyScatter = nullptr;

	//AI Patterns for pinky
	std::shared_ptr<AIPatterns> m_pinkyAIPatterns = nullptr;
	std::shared_ptr<Chase> m_pinkyChase = nullptr;
	std::shared_ptr<Scatter> m_pinkyScatter = nullptr;

	//AI Patterns for clyde
	std::shared_ptr<AIPatterns> m_clydeAIPatterns = nullptr;
	std::shared_ptr<Chase> m_clydeChase = nullptr;
	std::shared_ptr<Scatter> m_clydeScatter = nullptr;

	//AI Patterns for inky
	std::shared_ptr<AIPatterns> m_inkyAIPatterns = nullptr;
	std::shared_ptr<Chase> m_inkyChase = nullptr;
	std::shared_ptr<Scatter> m_inkyScatter = nullptr;
};

