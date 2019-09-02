#include "EnemyDispatcher.h"



EnemyDispatcher::EnemyDispatcher(std::shared_ptr<AIPatterns> initialAI, std::shared_ptr<Sprite> blinky, std::shared_ptr<Sprite> inky, std::shared_ptr<Sprite> clyde, std::shared_ptr<Sprite> pinky,
	std::shared_ptr<TileMap> map)
{
	m_originalAI = initialAI;
	m_originalMap = map;
	


	m_blinky.sprite = blinky;
	m_inky.sprite = inky;
	m_inky.spriteDependency = blinky;
	m_clyde.sprite = clyde;
	m_pinky.sprite = pinky;
	//init the modes first
	initChase();
	initScatter();
	initStarting();
	//mapping of the enemies using map
	m_enemies["blinky"] = m_blinky;
	m_enemies["inky"] = m_inky;
	m_enemies["clyde"] = m_clyde;
	m_enemies["pinky"] = m_pinky;
	initAI(initialAI);
	initFrightened();
}

void EnemyDispatcher::releaseInky()
{
	m_enemies["inky"].startingMovement = std::make_shared<LeavePen>();
}

void EnemyDispatcher::releaseClyde()
{
	m_enemies["clyde"].startingMovement = std::make_shared<LeavePen>();
}


EnemyDispatcher::~EnemyDispatcher()
{
}

void EnemyDispatcher::initChase()
{

	//blinky patterns
	m_blinky.chaseMode = std::make_shared<AggresiveChase>();

	//inky patterns
	m_inky.chaseMode = std::make_shared<RandomChase>();

	//Pinky patterns
	m_pinky.chaseMode = std::make_shared<AmbushChase>();

	//clyde patterns
	m_clyde.chaseMode = std::make_shared<PatrolChase>();
}

void EnemyDispatcher::initScatter()
{
	//blinky patterns
	m_blinky.scatterMode = std::make_shared<TopRightScatter>();

	//Pinky patterns
	m_pinky.scatterMode = std::make_shared<TopLeftScatter>();

	//clyde patterns
	m_clyde.scatterMode = std::make_shared<BotLeftScatter>();

	//inky patterns
	m_inky.scatterMode = std::make_shared<BotRightScatter>();
}

void EnemyDispatcher::initStarting()
{
	m_blinky.startingMovement = nullptr;
	m_pinky.startingMovement = std::make_shared<LeavePen>();
	m_clyde.startingMovement = std::make_shared<RightPen>();
	m_inky.startingMovement = std::make_shared<LeftPen>();
}

void EnemyDispatcher::initAI(std::shared_ptr<AIPatterns> AIPattern)
{
	for (auto& x: m_enemies)
	{
		x.second.spriteAI = AIPattern;
	}
}

void EnemyDispatcher::initFrightened()
{
	for (auto& enemy : m_enemies)
	{
		enemy.second.frightMode = std::make_shared<SlowFrightened>();
	}
}

void EnemyDispatcher::useScatter(float deltaTime)
{
	for (auto& enemy : m_enemies)
	{
		enemy.second.scatterMode->scatter(m_target, enemy.second.sprite, enemy.second.spriteAI, deltaTime);
	}
}

void EnemyDispatcher::useChase(float deltaTime)
{
	for (auto& enemy : m_enemies)
	{
		enemy.second.chaseMode->chase(m_target, enemy.second.sprite, enemy.second.spriteDependency, enemy.second.spriteAI, m_originalMap, deltaTime);
	}
}

void EnemyDispatcher::resetAI()
{
	//has to be shared pointer so that the value is getting sent instead and not modified directly
	for (auto& x : m_enemies)
	{
		x.second.spriteAI = std::make_shared<AIPatterns>(*m_originalAI);
	}
}

void EnemyDispatcher::setAIModes(int globalAIMode)
{
	for (auto& enemy : m_enemies)
	{
		//reset frightened mode if the sprite was already in slow mode
		if (enemy.second.sprite->getMoveMode() != MODE::FRIGHTENED) {
			enemy.second.frightMode = std::make_shared<SlowFrightened>();
		}
		//everyone but blinky get there starting movement changed back to the original
		if (enemy.second.sprite->getMoveMode() != MODE::STARTING && enemy.second.startingMovement != nullptr) {
			enemy.second.startingMovement = std::make_shared<LeavePen>();
		}
		//frightened mode until a timer is tripped
		if (enemy.second.sprite->getMoveMode() == MODE::FRIGHTENED) {
			enemy.second.sprite->setMoveMode(MODE::FRIGHTENED);
		}
		//starting in starting mod
		else if (enemy.second.startingMovement != nullptr && enemy.second.sprite->inPen())
		{
			enemy.second.sprite->setMoveMode(MODE::STARTING);
		}
		//both statements for globalAIMode
		else if (enemy.second.sprite->getMoveMode() != MODE::FRIGHTENED &&
			enemy.second.sprite->tileChanged &&
			!enemy.second.sprite->inTunnel() &&
			enemy.second.startingMovement == nullptr)
		{
			enemy.second.sprite->setMoveMode(globalAIMode);
		}
		else if (enemy.second.sprite->tileChanged &&
			!enemy.second.sprite->inPen() &&
			enemy.second.sprite->getMoveMode() != MODE::FRIGHTENED)
		{
			enemy.second.sprite->setMoveMode(globalAIMode);
		}
	}
}

void EnemyDispatcher::decideMode(float deltaTime)
{
	for (auto& enemy : m_enemies)
	{
		switch (enemy.second.sprite->getMoveMode())
		{
		case MODE::CHASE:
			enemy.second.chaseMode->chase(m_target, enemy.second.sprite, enemy.second.spriteDependency, enemy.second.spriteAI, m_originalMap, deltaTime);
			break;
		case MODE::SCATTER:
			enemy.second.scatterMode->scatter(m_target, enemy.second.sprite, enemy.second.spriteAI, deltaTime);
			break;
		case MODE::FRIGHTENED:
			enemy.second.frightMode->fright(enemy.second.sprite, enemy.second.spriteAI, m_originalMap, deltaTime);
			break;
		case MODE::STARTING:
			enemy.second.startingMovement->start(enemy.second.sprite, enemy.second.spriteAI, deltaTime);
			break;
		default:
			enemy.second.chaseMode->chase(m_target, enemy.second.sprite, enemy.second.spriteDependency, enemy.second.spriteAI, m_originalMap, deltaTime);
			break;
		}
	}
}

void EnemyDispatcher::targetHero(std::shared_ptr<Sprite> pacman, int enemyMode, float deltaTime)
{
	m_target = pacman;
	m_globalAIMode = enemyMode;
	setAIModes(m_globalAIMode);
	resetAI();
	decideMode(deltaTime);
}

void EnemyDispatcher::collided(std::shared_ptr<Sprite> pacman)
{
	for (auto& enemy : m_enemies)
	{
		if (pacman->pacmanIsHit(*enemy.second.sprite) && enemy.second.sprite->getMoveMode() != MODE::FRIGHTENED)
		{
			enemy.second.sprite->resetSprite();
		}
		if (pacman->pacmanIsHit(*enemy.second.sprite) && enemy.second.sprite->getMoveMode() == MODE::FRIGHTENED)
		{

			enemy.second.frightMode = std::make_shared<BackToStart>();
		}

	}
}
