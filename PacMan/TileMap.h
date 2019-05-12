#pragma once
#include "Tiles.h"
#include "Texture2D.h"
#include <memory>
#include <fstream>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class BindedTile {
public:
	Texture2D texture;
	Tiles tile;
	char c_tile;
	glm::vec2 position;
	BindedTile(Texture2D texture, Tiles tile, char c_tile, glm::vec2 m_position) : texture(texture), tile(tile), c_tile(c_tile), position(m_position) {}
};

class TileMap
{
	typedef std::vector<std::vector<char>> char2d;
	typedef std::vector < std::vector<BindedTile>> tile2d;
public:
	TileMap(const char * fileName, float tilength);
	auto getMap() { return tileArr; };
	auto getRowSize() { return m_rows; };
	auto getColSize() { return m_cols; };
	auto getBindedTile(int i, int j) { return tileArr[i][j]; };
	auto getValidPositions() { return m_validPositions; }

	void updateTileMap();
	void clearTile(int row, int col);
	void putTile(int row, int col);
	auto getChars() { return m_board; };
	~TileMap();
private:
	void readFile(const char * fileName);
	enum TILE {
		NILL = '0',
		FRUIT = 'f',
		PELLET = 'b',
		DOT = '-',
		GATE = 'g',
		BORDER = '|',
		AIBOUND1 = 'a',
		AIBOUND2 = '=',
		AIDIR = '+'
	};
	NullTile nullTile;
	FruitTile fruitTile;
	PelletTile pelletTile;
	DotTile dotTile;
	GateTile gateTile;
	BorderTile borderTile;

	std::shared_ptr<Texture2D> nullTexture = std::make_shared<Texture2D>("black.jpg");
	std::shared_ptr<Texture2D> fruitTexture = std::make_shared<Texture2D>("fruit.jpg");
	std::shared_ptr<Texture2D> pelletTexture = std::make_shared<Texture2D>("pellet.jpg");
	std::shared_ptr<Texture2D> dotTexture = std::make_shared<Texture2D>("dot.jpg");
	std::shared_ptr<Texture2D> gateTexture = std::make_shared<Texture2D>("gate.jpg");
	std::shared_ptr<Texture2D> borderTexture = std::make_shared<Texture2D>("border.jpg");

	BindedTile tileType(char tileChar, glm::vec2 position);
	tile2d tileArr;
	tile2d originalArr;
	float m_tileLength;

	std::vector<glm::vec2> m_validPositions;

	std::vector<char> splitStringToChars(std::string fullString, char delimiter);
	char2d m_board;
	
	int m_rows;
	int m_cols;
};

