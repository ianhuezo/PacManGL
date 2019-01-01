#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Texture2D.h"
class Sprite
{
public:
	auto getModel() { return m_model; };
	virtual ~Sprite();
	virtual void drawSprite() {};
	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
protected:
	glm::mat4 m_model;
};

