#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Texture2D.h"
class Sprite
{
public:
	Sprite(float tileLength, const char * filePath, glm::vec2(indices));
	auto getModel() { return m_model; };
	virtual ~Sprite();
	void drawSprite();
	virtual void moveUp();
	virtual void moveDown();
	virtual void moveRight();
	virtual void moveLeft();
protected:
	//the position of the model
	float m_tileLength;
	glm::mat4 m_model;
	Texture2D* m_texture;
	//row col compared to the tiles
	glm::vec2 m_indices;
};

class PacMan: public Sprite
{
public:
	PacMan(float tileLength, const char * filePath, glm::vec2(indices)) :
		Sprite(tileLength, filePath, glm::vec2(indices)) {}
	virtual void moveUp();
	virtual void moveDown();
	virtual void moveLeft();
	virtual void moveRight();
};

