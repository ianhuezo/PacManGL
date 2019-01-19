#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Texture2D.h"
#include <memory>
#include <iostream>
#include <math.h>
#include "TileMap.h"

class Sprite
{
	//should be 36 rows by 28 columns, need to refactor, for now just added more than needed columns
	#define ROW_SIZE 36
	#define COL_SIZE 28
public:
	Sprite(float tileLength, const char * filePath, glm::vec2(indices), TileMap& charMap);
	auto getModel() { return mm_model; };
	auto getTileIndices() { return mm_indices; };
	auto getModelPosition() { return mm_pixelPosition; };

	virtual ~Sprite() {};
	void drawSprite();
	float spriteSpeed = 100;

	//movements for pacman
	void generalMove(float& pixelPosition, float& fixedPosition, float& index,const float& velocity, float indexNum);
	virtual void moveUp(float deltaTime);
	virtual void moveDown(float deltaTime);
	virtual void moveRight(float deltaTime);
	virtual void moveLeft(float deltaTime);
	virtual void moveStill(float deltaTime);
	//functions return the char at the current tile
	char checkLeft();
	char checkRight();
	char checkUp();
	char checkDown();
	//tells sprite if tile has changed for movement
	bool tileChanged = true;

	TileMap charMap;

protected:
	//the calculated/acquired tile lengths
	float mm_tileLength;
	float mm_halfTileLength;
	

	//model 
	glm::mat4 mm_model;
	std::shared_ptr<Texture2D> mm_texture;

	//array for each tile position in mm_pixelPosition
	//row col compared to the tiles
	glm::vec2 mm_indices;
	//actual pixel position i.e. top left corner of every tile
	glm::vec2 mm_pixelPosition;
	//current position on the tile(variable)
	glm::vec2 mm_fixedPosition;
};

