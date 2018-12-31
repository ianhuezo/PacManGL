#pragma once
#include "Tiles.h"
#include "Texture2D.h"
#include <memory>
#include <fstream>
#include <string>
#include <vector>
class BindedTile {
public:
	Texture2D texture;
	Tiles tile;
	BindedTile(Texture2D texture, Tiles tile) : texture(texture), tile(tile) {}
	//BindedTile& operator = (const BindedTile& bt) { texture = bt.texture; tile = bt.tile; return *this; }
};

class TileMap
{
	typedef std::vector<std::vector<char>> char2d;
	typedef std::vector < std::vector<BindedTile>> tile2d;
public:
	TileMap(const char * fileName);
	auto getMap() { return tileArr; };
	void updateTileMap();
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
	NullTile nullTile;
	FruitTile fruitTile;
	PelletTile pelletTile;
	DotTile dotTile;
	GateTile gateTile;
	BorderTile borderTile;

	std::shared_ptr<Texture2D> nullTexture = std::make_shared<Texture2D>("black.jpg");
	std::shared_ptr<Texture2D> fruitTexture = std::make_shared<Texture2D>("fruit.jpg");
	std::shared_ptr<Texture2D> pelletTexture = std::make_shared<Texture2D>("green.jpg");
	std::shared_ptr<Texture2D> dotTexture = std::make_shared<Texture2D>("green.jpg");
	std::shared_ptr<Texture2D> gateTexture = std::make_shared<Texture2D>("gate.png");
	std::shared_ptr<Texture2D> borderTexture = std::make_shared<Texture2D>("blue.jpg");

	BindedTile tileType(char tileChar);
	tile2d tileArr;

	void readFile(const char * fileName);
	std::vector<char> splitStringToChars(std::string fullString, char delimiter);
	char2d m_board;
};

