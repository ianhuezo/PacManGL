#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <random>
#include "Texture2D.h"
#include <iostream>
class Tiles
{
public:
	//assigns the point value
	Tiles();
	virtual ~Tiles() = default;
	virtual void assignTileValue() { mm_tileValue = 0; };
	//assigns the texture to the tile
	virtual void assignTexture(Texture2D& texture) { texture.assignTexture(); };

	/*getters for tile attributes*/
	//returns the tiles points value
	auto getTileValue() { return mm_tileValue; };
	//returns the tile's width/height
	//returns the tile's x/y coordinates
	glm::vec2 m_position;

protected:
	int mm_tileValue;
private:
	//What can be on each tile
	//unique to each tile

	//potentially shared with a different tile
	//non accessible tiles i.e. the borders
	//pac pellet - eaten to turn enemies to ghosts and score
	//pac dot - tile that just gives points
	//fruit - tile that gives BONUS points given a certain amount of pacdots
	//pacman - maybe not a tile attribute, but added just for reference
	//enemies - maybe not a tile attribute, but added just for reference

	//i.e. the width and height of each tile
};
//for setTexture2D I did a different function call for each texture
//making it simpler to follow

class FruitTile : public Tiles
{
	enum FRUIT
	{
		CHERRY = 100,
		STRAWBERRY = 300,
		ORANGE = 500,
		APPLE = 700,
		MELON = 1000,
		BOSS = 2000,
		BELL = 3000,
		KEY = 5000
	};
public:
	virtual void assignTileValue() { assignRandomFruit(); mm_tileValue = m_randFruit; };
	virtual void assignTexture(Texture2D& texture) { texture.assignTexture(); };

private:
	int m_randFruit;
	void assignRandomFruit();
};

class PelletTile : public Tiles
{
public:
	virtual void assignTileValue() { mm_tileValue = 50; };
	virtual void assignTexture(Texture2D& texture) { texture.assignTexture(); };

};

class DotTile : public Tiles
{
public:
	virtual void assignTileValue() { mm_tileValue = 10; };
	virtual void assignTexture(Texture2D& texture) { texture.assignTexture(); };

};

class NullTile : public Tiles
{
public:
	virtual void assignTexture(Texture2D& texture) { texture.assignTexture(); };

};

class BorderTile : public Tiles
{
public:
	virtual void assignTexture(Texture2D& texture) { texture.assignTexture(); };

};

class GateTile : public Tiles
{
public:
	virtual void assignTexture(Texture2D& texture) { texture.assignTexture(); };

};

