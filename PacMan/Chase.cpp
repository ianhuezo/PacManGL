#include "Chase.h"

Chase::Chase()
{
}

Chase::~Chase()
{
}


std::shared_ptr<InputCommand> AggresiveChase::chase(Sprite & pacman, Sprite & enemyAI, TileMap & map)
{

	float pacX = pacman.getTileIndices().x;
	float pacY = pacman.getTileIndices().y;

	float eneX = enemyAI.getTileIndices().x;
	float eneY = enemyAI.getTileIndices().y;


	float resultX = pacX - eneX;
	float resultY = pacY - eneY;
	//if enemy wants to go left
	if (resultX < 0 && enemyAI.checkLeft() != '|')
	{
		return std::make_shared<LeftCommand>();
	}
	//if enemy wants to go right
	else if (resultX > 0 && enemyAI.checkRight() != '|')
	{
		return std::make_shared<RightCommand>();
	}
	//enemy goes down
	else if (resultY > 0 && enemyAI.checkDown() != '|')
	{
		return std::make_shared<DownCommand>();
	}
	//enemy goes up
	else if (resultY < 0 && enemyAI.checkUp() != '|')
	{
		return std::make_shared<UpCommand>();
	}
	//else if (resultY == 0 && enemyAI.checkLeft() != '|'){
	//	return std::make_shared<LeftCommand>();
	//}
	else {
		return std::make_shared<StillCommand>();
	}
}

std::shared_ptr<InputCommand> RandomChase::chase(Sprite & pacman, Sprite & enemyAI, TileMap & map)
{
	return std::shared_ptr<LeftCommand>();
}

std::shared_ptr<InputCommand> PatrolChase::chase(Sprite & pacman, Sprite & enemyAI, TileMap & map)
{
	return std::shared_ptr<LeftCommand>();
}

std::shared_ptr<InputCommand> AmbushChase::chase(Sprite & pacman, Sprite & enemyAI, TileMap & map)
{
	return std::shared_ptr<LeftCommand>();
}

EnemyHandler::EnemyHandler()
{
	enemyChase = std::make_shared<AggresiveChase>();
}
