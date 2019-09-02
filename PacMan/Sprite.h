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
#include "SpriteDirection.h"
#include "EnemyMode.h"

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
	auto getHalfTileDistance() { return mm_halfTileLength; };
	auto getInitialPosition() { return mm_initialPosition; };
	auto getTileDistance() { return mm_tileLength; };
	int getMoveMode() { return m_spriteMode; };
	int getPreviousMoveMode() { return m_previousMode; };

	//the current mode of the sprite
	void setMoveMode(int mode);

	virtual ~Sprite() {};
	void drawSprite();
	float spriteSpeed = 100;
	//movements for sprite
	void generalMove(float& pixelPosition, float& fixedPosition, float& index,const float& velocity, float indexNum);
	virtual void moveUp(float deltaTime);
	virtual void moveDown(float deltaTime);
	virtual void moveRight(float deltaTime);
	virtual void moveLeft(float deltaTime);
	virtual void moveStill(float deltaTime);
	//sprite is in pen
	bool inPen() { return m_inPen; };
	void setPen(bool withinPen) { m_inPen = withinPen; };
	//functions return the char at the current tile
	char checkLeft();
	char checkRight();
	char checkUp();
	char checkDown();
	char checkCurrent();
	//members that keep track of the sprites previous position
	void setPreviousPosition(glm::vec2 position) { mm_previousPosition = position; };
	glm::vec2 getPreviousPosition() { return mm_previousPosition; };
	//members that keep track of the distance to pacman
	void setDistanceToPacman(int distance) { mm_distanceToPacman = distance; };
	int getDistanceToPacman() { return mm_distanceToPacman; };


	//requested mode of the sprite


	//tells sprite if tile has changed for movement
	bool tileChanged = true;
	bool inTunnel() { return m_inTunnel; }

	void resetSprite();

	//return the current direction the sprite is moving
	int spriteDirection = MOVE::STILL;

	TileMap charMap;

	//whether pacman touches a sprite
	bool pacmanIsHit(const Sprite& enemy);

protected:
	const char * mm_filepath;
	std::shared_ptr<TileMap> mm_charMap;
	glm::vec2 mm_initialPosition;
	//the calculated/acquired tile lengths
	float mm_tileLength;
	float mm_halfTileLength;
	//model 
	glm::mat4 mm_model;
	std::shared_ptr<Texture2D> mm_texture;

	//tunnel logic
	glm::vec2 rightTunnel;
	glm::vec2 leftTunnel;

	glm::mat4 tunnelPositionLeft;
	glm::mat4 tunnelPositionRight;

	bool m_inTunnel = false;

	//pen logic
	bool m_inPen = true;

	//the mode i.e. chase, scatter, frightened the ghost is in
	int m_spriteMode = MODE::STARTING;
	int m_previousMode = MODE::STARTING;
	//the requested mode for the sprite class

	//array for each tile position in mm_pixelPosition
	//row col compared to the tiles
	glm::vec2 mm_indices;
	//actual pixel position i.e. top left corner of every tile
	glm::vec2 mm_pixelPosition;
	//current position on the tile(variable)
	glm::vec2 mm_fixedPosition;
	//previous position on the tile(variable)
	glm::vec2 mm_previousPosition = glm::vec2(0, 0);
	//distance to pacman
	int mm_distanceToPacman = FLT_MAX;

	bool killedPacman = false;

	std::shared_ptr<Sprite> mm_originalSprite = nullptr;
};

