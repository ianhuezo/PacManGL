#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "Sprite.h"
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>

class InputCommand
{
public:
	InputCommand();
	virtual void execute(Sprite& sprite) = 0;
	virtual ~InputCommand();
};

class UpCommand : public InputCommand
{
public:
	virtual void execute(Sprite& sprite) { sprite.moveUp(); }
};

class DownCommand : public InputCommand
{
public:
	virtual void execute(Sprite& sprite) { sprite.moveDown(); }
};

class RightCommand : public InputCommand
{
public:
	virtual void execute(Sprite& sprite) { sprite.moveRight(); }
};

class LeftCommand : public InputCommand
{
public:
	virtual void execute(Sprite& sprite) { sprite.moveLeft(); }
};

class InputHandler
{
public:
	InputHandler(GLFWwindow* window);
	InputCommand* handleInput() {
		if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			return moveUp;
		}
		if (glfwGetKey(m_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			return moveRight;
		}
		if (glfwGetKey(m_window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			return moveLeft;
		}
		if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			return moveDown;
		}
		return NULL;
	}
private:
	InputCommand* moveLeft;
	InputCommand* moveRight;
	InputCommand* moveUp;
	InputCommand* moveDown;
	GLFWwindow* m_window;



private:
	
};