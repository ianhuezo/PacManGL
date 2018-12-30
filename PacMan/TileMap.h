#pragma once
#include "Tiles.h"
#include "Texture2D.h"
#include <memory>
#include <fstream>
#include <string>
#include <vector>

class TileMap
{
	typedef std::vector<std::vector<char>> char2d;
	typedef std::vector < std::vector<Tiles>> tile_ptrs;
public:
	TileMap(const char * fileName);
	auto getMap() { return tileArr; };
	void updateTileMap();
	void tileType(char tileChar);
	auto getChars() { return m_board; };
	~TileMap();
private:
	enum TILE {
		NILL = '0',
		FRUIT = 'f',
		PELLET = 'b',
		DOT = '-',
		GATE = 'g',
		BORDER = '|'
	};
	//std::shared_ptr<NullTile> nullTile = std::make_shared<NullTile>();
	//std::shared_ptr<FruitTile> fruitTile = std::make_shared<FruitTile>();
	//std::shared_ptr<PelletTile> pelletTile = std::make_shared<PelletTile>();
	//std::shared_ptr<DotTile> dotTile = std::make_shared<DotTile>();
	//std::shared_ptr<GateTile> gateTile = std::make_shared<GateTile>();
	//std::shared_ptr<BorderTile> borderTile = std::make_shared<BorderTile>();

	NullTile nullTile;
	BorderTile borderTile;

	Texture2D nullTexture;
	Texture2D borderTexture;


	tile_ptrs tileArr;

	void readFile(const char * fileName);
	std::vector<char> splitStringToChars(std::string fullString, char delimiter);
	char2d m_board;
};

