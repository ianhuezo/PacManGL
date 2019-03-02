#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "Sprite.h"
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <memory>
#include "SpriteDirection.h"

// stackoverflow page on comparing classes https://stackoverflow.com/questions/1765122/equality-test-for-derived-classes-in-c
class InputCommand
{
public:
	InputCommand();
	virtual void execute(Sprite& sprite, float deltaTime) = 0;
	int command;
	int spriteState;

	friend
	bool operator==(InputCommand const& lhs, InputCommand const& rhs) {
		return lhs.isEqual(rhs);
	}
	friend
	bool operator!=(InputCommand const& lhs, InputCommand const& rhs)
	{
		return !(lhs == rhs);
	}
	virtual ~InputCommand();
protected:
	virtual bool isEqual(InputCommand const& other) const {
		return spriteState == other.spriteState;
	}
};

class UpCommand : public InputCommand
{
public:
	virtual void execute(Sprite& sprite, float deltaTime) { sprite.moveUp(deltaTime); }
	int spriteState = MOVE::UP;
protected:
	virtual bool isEqual(InputCommand const& other) const {
		if (UpCommand const* p = dynamic_cast<UpCommand const*>(&other)) {
			return InputCommand::isEqual(other) && spriteState == p->spriteState;
		}
		else {
			return false;
		}
	}
};

class DownCommand : public InputCommand
{
public:
	virtual void execute(Sprite& sprite, float deltaTime) { sprite.moveDown(deltaTime); }
	int spriteState = MOVE::DOWN;
protected:
	virtual bool isEqual(InputCommand const& other) const {
		if (DownCommand const* p = dynamic_cast<DownCommand const*>(&other)) {
			return InputCommand::isEqual(other) && spriteState == p->spriteState;
		}
		else {
			return false;
		}
	}
};

class RightCommand : public InputCommand
{
public:
	virtual void execute(Sprite& sprite, float deltaTime) { sprite.moveRight(deltaTime); }
	int spriteState = MOVE::RIGHT;
protected:
	virtual bool isEqual(InputCommand const& other) const {
		if (RightCommand const* p = dynamic_cast<RightCommand const*>(&other)) {
			return InputCommand::isEqual(other) && spriteState == p->spriteState;
		}
		else {
			return false;
		}
	}
};

class LeftCommand : public InputCommand
{
public:
	virtual void execute(Sprite& sprite, float deltaTime) { sprite.moveLeft(deltaTime); }
	int spriteState = MOVE::LEFT;
protected:
	virtual bool isEqual(InputCommand const& other) const {
		if (LeftCommand const* p = dynamic_cast<LeftCommand const*>(&other)) {
			return InputCommand::isEqual(other) && spriteState == p->spriteState;
		}
		else {
			return false;
		}
	}
};

class StillCommand : public InputCommand
{
public:
	virtual void execute(Sprite& sprite, float deltaTime) { sprite.moveStill(deltaTime); }
	int spriteState = MOVE::STILL;
protected:
	virtual bool isEqual(InputCommand const& other) const {
		if (StillCommand const* p = dynamic_cast<StillCommand const*>(&other)) {
			return InputCommand::isEqual(other) && spriteState == p->spriteState;
		}
		else {
			return false;
		}
	}
};

class InputHandler
{
public:
	InputHandler(GLFWwindow* window);
	std::shared_ptr<InputCommand> currentCommand = NULL;
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
		if (currentCommand == NULL)
		{
			return moveNone;
		}
		return NULL;
	}
private:
	std::shared_ptr<InputCommand> moveLeft;
	std::shared_ptr<InputCommand> moveRight;
	std::shared_ptr<InputCommand> moveUp;
	std::shared_ptr<InputCommand> moveDown;
	std::shared_ptr<InputCommand> moveNone;
	GLFWwindow* m_window;

	
};