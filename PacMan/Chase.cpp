#include "Chase.h"

Chase::Chase()
{

}


Chase::~Chase()
{
}

std::shared_ptr<InputCommand> AggresiveChase::chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern)
{
	return std::shared_ptr<StillCommand>();
}

std::shared_ptr<InputCommand> RandomChase::chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern)
{
	return std::shared_ptr<LeftCommand>();
}

std::shared_ptr<InputCommand> PatrolChase::chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern)
{
	return std::shared_ptr<LeftCommand>();
}

std::shared_ptr<InputCommand> AmbushChase::chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern)
{
	return std::shared_ptr<LeftCommand>();
}

EnemyHandler::EnemyHandler()
{
	enemyChase = std::make_shared<AggresiveChase>();
}
