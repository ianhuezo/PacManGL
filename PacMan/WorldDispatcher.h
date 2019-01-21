#pragma once
#include "Sprite.h"
#include "PacManSprite.h"
#include "InputCommand.h"
#include <iostream>
#include <memory>
class WorldDispatcher
{
public:
	void playerDispatch(const std::shared_ptr<PacManSprite>& pacman, std::shared_ptr<InputCommand> command, float deltaTime);

private:
	std::shared_ptr<InputCommand> playerDispatcher = std::make_shared<LeftCommand>();
	void playerConstrain(const std::shared_ptr<Sprite>& sprite, std::shared_ptr<InputCommand>& command, std::shared_ptr<InputCommand>& dispatcher,float deltaTime);

};

