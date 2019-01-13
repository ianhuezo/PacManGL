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

	moveLeft->x = -1;
	moveLeft->y = 0;

	moveRight->x = 1;
	moveRight->y = 0;

	moveUp->y = -1;
	moveUp->x = 0;

	moveDown->x = 0;
	moveDown->y = 1;
}

InputCommand::~InputCommand()
{
}
