#include "InputCommand.h"

InputCommand::InputCommand()
{
}

InputHandler::InputHandler(GLFWwindow * window)
{
	m_window = window;
	moveLeft = new LeftCommand();
	moveRight = new RightCommand();
	moveDown = new DownCommand();
	moveUp = new UpCommand();

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
