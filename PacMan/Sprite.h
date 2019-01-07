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
	//should be 36 rows by 28 columns, need to refactor, for now just added more than needed columns
	#define ROW_SIZE 36
	#define COL_SIZE 28
public:
	Sprite(float tileLength, const char * filePath, glm::vec2(indices));
	auto getModel() { return m_model; };
	auto getTileIndices() { return m_indices; };
	auto getModelPosition() { return mm_pixelPosition; };

	virtual ~Sprite() {};
	void drawSprite();
	float spriteSpeed = 100;
	//number is used for subtraction or addition
	void generalMove(float& pixelPosition, float& fixedPosition, float& index, float& deltaTime, float number);
	virtual void moveUp(float deltaTime);
	virtual void moveDown(float deltaTime);
	virtual void moveRight(float deltaTime);
	virtual void moveLeft(float deltaTime);
protected:
	//the position of the model
	float m_tileLength;
	float halfTileLength;
	glm::mat4 m_model;
	std::shared_ptr<Texture2D> m_texture;

	bool movementEnabled = true;

	//array for each tile position in mm_pixelPosition
	glm::vec2 tilePositions[36][28];
	//row col compared to the tiles
	glm::vec2 m_indices;
	//actual pixel position i.e. top left corner of every tile
	glm::vec2 mm_pixelPosition;
	//current position on the tile(variable)
	glm::vec2 mm_fixedPosition;
};

class PacMan: public Sprite
{
public:
	PacMan(float tileLength, const char * filePath, glm::vec2(indices)) :
		Sprite(tileLength, filePath, glm::vec2(indices)) {}
	~PacMan() {};
	virtual void moveUp(float deltaTime);
	virtual void moveDown(float deltaTime);
	virtual void moveLeft(float deltaTime);
	virtual void moveRight(float deltaTime);
private:
	std::shared_ptr<Texture2D> m_textureUp = std::make_shared<Texture2D>("pacup.png");
	std::shared_ptr<Texture2D> m_textureDown = std::make_shared<Texture2D>("pacdown.png");
	std::shared_ptr<Texture2D> m_textureLeft = std::make_shared<Texture2D>("pacleft.png");
	std::shared_ptr<Texture2D> m_textureRight = std::make_shared<Texture2D>("pacright.png");
};

