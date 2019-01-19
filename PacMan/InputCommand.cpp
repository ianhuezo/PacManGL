#include "InputCommand.h"

InputCommand::InputCommand()
{
}

InputHandler::InputHandler(GLFWwindow * window)
{
	m_window = window;
	moveLeft = std::make_shared<LeftCommand>();
	moveRight = std::make_shared<RightCommand>();
	moveDown = std::make_shared<DownCommand>();
	moveUp = std::make_shared<UpCommand>();
	moveNone = std::make_shared<StillCommand>();

	moveLeft->command = MOVE::LEFT;
	moveRight->command = MOVE::RIGHT;
	moveUp->command = MOVE::UP;
	moveDown->command = MOVE::DOWN;
	moveNone->command = MOVE::STILL;
}

InputCommand::~InputCommand()
{
}
