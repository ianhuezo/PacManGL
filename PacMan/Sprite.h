#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Texture2D.h"
#include <memory>
#include <iostream>
#include <math.h>

class Sprite
{
	#define ROW_SIZE 28
	#define COL_SIZE 36
public:
	Sprite(float tileLength, const char * filePath, glm::vec2(indices));
	auto getModel() { return m_model; };
	virtual ~Sprite() {};
	void drawSprite();
	void updateIndices();
	virtual void moveUp();
	virtual void moveDown();
	virtual void moveRight();
	virtual void moveLeft();
	void disableMovement() { movementEnabled = false; };
	void enableMovement() { movementEnabled = true; };
protected:
	//the position of the model
	float m_tileLength;
	glm::mat4 m_model;
	std::shared_ptr<Texture2D> m_texture;

	bool movementEnabled = true;

	//array for each tile position
	glm::vec2 tilePositions[ROW_SIZE][COL_SIZE];
	//row col compared to the tiles
	glm::vec2 m_indices;
	//actual pixel position
	glm::vec2 mm_pixelPosition;
	//current position on the tile(variable)
	glm::vec2 mm_fixedPosition;
};

class PacMan: public Sprite
{
public:
	PacMan(float tileLength, const char * filePath, glm::vec2(indices)) :
		Sprite(tileLength, filePath, glm::vec2(indices)) {}
	~PacMan();
	virtual void moveUp();
	virtual void moveDown();
	virtual void moveLeft();
	virtual void moveRight();
private:
	std::shared_ptr<Texture2D> m_textureUp = std::make_shared<Texture2D>("pacup.png");
	std::shared_ptr<Texture2D> m_textureDown = std::make_shared<Texture2D>("pacdown.png");
	std::shared_ptr<Texture2D> m_textureLeft = std::make_shared<Texture2D>("pacleft.png");
	std::shared_ptr<Texture2D> m_textureRight = std::make_shared<Texture2D>("pacright.png");
};

