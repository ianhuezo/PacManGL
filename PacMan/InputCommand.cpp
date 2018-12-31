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
}

InputCommand::~InputCommand()
{
}
