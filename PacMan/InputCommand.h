#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "Sprite.h"
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <memory>

class InputCommand
{
public:
	InputCommand();
	virtual void execute(Sprite& sprite, float deltaTime) = 0;
	int x;
	int y;
	virtual ~InputCommand();
};

class UpCommand : public InputCommand
{
public:
	virtual void execute(Sprite& sprite, float deltaTime) { sprite.moveUp(deltaTime); }
};

class DownCommand : public InputCommand
{
public:
	virtual void execute(Sprite& sprite, float deltaTime) { sprite.moveDown(deltaTime); }
};

class RightCommand : public InputCommand
{
public:
	virtual void execute(Sprite& sprite, float deltaTime) { sprite.moveRight(deltaTime); }
};

class LeftCommand : public InputCommand
{
public:
	virtual void execute(Sprite& sprite, float deltaTime) { sprite.moveLeft(deltaTime); }
};

class InputHandler
{
public:
	InputHandler(GLFWwindow* window);
	~InputHandler()
	{

	}
	std::shared_ptr<InputCommand> handleKeyInput() {
		if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			currentCommand = moveUp;
			return moveUp;
		}
		if (glfwGetKey(m_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			currentCommand = moveRight;
			return moveRight;
		}
		if (glfwGetKey(m_window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			currentCommand = moveLeft;
			return moveLeft;
		}
		if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			currentCommand = moveDown;
			return moveDown;
		}
		if (currentCommand != NULL)
		{
			return currentCommand;
		}
		return NULL;
	}
	virtual InputCommand* handleBotInput() { return NULL; };
private:
	std::shared_ptr<InputCommand> moveLeft;
	std::shared_ptr<InputCommand> moveRight;
	std::shared_ptr<InputCommand> moveUp;
	std::shared_ptr<InputCommand> moveDown;
	std::shared_ptr<InputCommand> currentCommand = NULL;
	GLFWwindow* m_window;

	
};