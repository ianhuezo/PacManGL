#include "WorldDispatcher.h"


void WorldDispatcher::playerDispatch(const std::shared_ptr<PacManSprite>& pacman, std::shared_ptr<InputCommand> command, float deltaTime)
{
	playerConstrain(pacman, command, playerDispatcher, deltaTime);
}
//note: could use pattern here, but I felt it wasn't necessary and makes more sense 
void WorldDispatcher::playerConstrain(const std::shared_ptr<Sprite>& sprite, std::shared_ptr<InputCommand>& command, std::shared_ptr<InputCommand>& dispatcher,float deltaTime)
{
	if (sprite->checkUp() != '|'  && command->command == MOVE::UP && sprite->tileChanged && sprite->checkUp() != 'g')
	{
		dispatcher = command;
	}
	else if (sprite->checkLeft() != '|'  && command->command == MOVE::LEFT && sprite->tileChanged && sprite->checkLeft() != 'g')
	{
		dispatcher = command;
	}
	else if (sprite->checkRight() != '|'  && command->command == MOVE::RIGHT && sprite->tileChanged && sprite->checkRight() != 'g')
	{
		dispatcher = command;
	}
	else if (sprite->checkDown() != '|'  && command->command == MOVE::DOWN && sprite->tileChanged && sprite->checkDown() != 'g')
	{
		dispatcher = command;
	}
	//updates sprite movement if the movement is not on a border
	if (sprite->checkUp() != '|' && dispatcher->command == MOVE::UP  && sprite->checkUp() != 'g')
	{
		dispatcher->execute(*sprite, deltaTime);
		dispatcher->spriteState = MOVE::UP;
	}
	else if (sprite->checkLeft() != '|' && dispatcher->command == MOVE::LEFT  && sprite->checkLeft() != 'g')
	{
		dispatcher->execute(*sprite, deltaTime);
		dispatcher->spriteState = MOVE::LEFT;
	}
	else if (sprite->checkRight() != '|' && dispatcher->command == MOVE::RIGHT  && sprite->checkRight() != 'g')
	{
		dispatcher->execute(*sprite, deltaTime);
		dispatcher->spriteState = MOVE::RIGHT;
	}
	else if (sprite->checkDown() != '|' && dispatcher->command == MOVE::DOWN  && sprite->checkDown() != 'g')
	{
		dispatcher->execute(*sprite, deltaTime);
		dispatcher->spriteState = MOVE::DOWN;
	}
	else {
		dispatcher->spriteState = MOVE::STILL;
	}
}
