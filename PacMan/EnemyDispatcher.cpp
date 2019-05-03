#include "EnemyDispatcher.h"



EnemyDispatcher::EnemyDispatcher(std::shared_ptr<AIPatterns> initialAI, std::shared_ptr<Sprite> blinky, std::shared_ptr<Sprite> inky, std::shared_ptr<Sprite> clyde, std::shared_ptr<Sprite> pinky,
	std::shared_ptr<TileMap> map)
{
	m_originalAI = initialAI;
	m_originalMap = map;
	m_blinky = blinky;
	m_inky = inky;
	m_clyde = clyde;
	m_pinky = pinky;

	initAI(initialAI);
	initChase();
	initScatter();
}


EnemyDispatcher::~EnemyDispatcher()
{
}

void EnemyDispatcher::initChase()
{
	//blinky patterns
	m_blinkyChase = std::make_shared<AggresiveChase>();

	//inky patterns
	m_inkyChase = std::make_shared<RandomChase>();

	//Pinky patterns
	m_pinkyChase = std::make_shared<AmbushChase>();

	//clyde patterns
	m_clydeChase = std::make_shared<PatrolChase>();
}

void EnemyDispatcher::initScatter()
{
	//blinky patterns
	m_blinkyScatter = std::make_shared<TopRightScatter>();

	//Pinky patterns
	m_pinkyScatter = std::make_shared<TopLeftScatter>();

	//clyde patterns
	m_clydeScatter = std::make_shared<BotLeftScatter>();

	//inky patterns
	m_inkyScatter = std::make_shared<BotRightScatter>();
}

void EnemyDispatcher::initAI(std::shared_ptr<AIPatterns> AIPattern)
{
	//blinky patterns
	m_blinkyAIPatterns = AIPattern;

	//Pinky patterns
	m_pinkyAIPatterns = AIPattern;

	//clyde patterns
	m_clydeAIPatterns = AIPattern;

	//inky patterns
	m_inkyAIPatterns = AIPattern;
}

void EnemyDispatcher::useScatter(float deltaTime)
{
	m_blinkyScatter->scatter(m_target, m_blinky, m_blinkyAIPatterns, deltaTime);
	m_pinkyScatter->scatter(m_target, m_pinky, m_pinkyAIPatterns, deltaTime);
	m_clydeScatter->scatter(m_target, m_clyde, m_clydeAIPatterns, deltaTime);
	m_inkyScatter->scatter(m_target, m_inky, m_inkyAIPatterns, deltaTime);
}

void EnemyDispatcher::useChase(float deltaTime)
{
	//important to keep blinky before inky for code to execute correctly in order
	m_blinkyChase->chase(m_target, m_blinky, nullptr, m_blinkyAIPatterns, m_originalMap, deltaTime);

	m_inkyChase->chase(m_target, m_inky, m_blinky, m_inkyAIPatterns, m_originalMap, deltaTime);

	m_pinkyChase->chase(m_target, m_pinky, nullptr, m_pinkyAIPatterns, m_originalMap, deltaTime);

	m_clydeChase->chase(m_target, m_clyde, nullptr, m_clydeAIPatterns, m_originalMap, deltaTime);
}

void EnemyDispatcher::resetAI()
{
	//has to be shared pointer so that the value is getting sent instead and not modified directly
	//blinky
	m_blinkyAIPatterns = std::make_shared<AIPatterns>(*m_originalAI);
	//pinky
	m_pinkyAIPatterns = std::make_shared<AIPatterns>(*m_originalAI);
	//clyde
	m_clydeAIPatterns = std::make_shared<AIPatterns>(*m_originalAI);
	//inky
	m_inkyAIPatterns = std::make_shared<AIPatterns>(*m_originalAI);
}

void EnemyDispatcher::targetHero(std::shared_ptr<Sprite> pacman, int enemyMode, float deltaTime)
{
	m_target = pacman;
	resetAI();
	useChase(deltaTime);
}
