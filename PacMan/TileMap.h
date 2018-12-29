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
	FruitTile fruitTile;
	PelletTile pelletTile;
	DotTile dotTile;
	GateTile gateTile;
	BorderTile borderTile;

	//std::shared_ptr<Texture2D> nullTexture = std::make_shared<Texture2D>("black.jpg");
	//std::shared_ptr<Texture2D> fruitTexture = std::make_shared<Texture2D>("green.jpg");
	//std::shared_ptr<Texture2D> pelletTexture = std::make_shared<Texture2D>("green.jpg");
	//std::shared_ptr<Texture2D> dotTexture = std::make_shared<Texture2D>("blue.jpg");
	//std::shared_ptr<Texture2D> borderTexture = std::make_shared<Texture2D>("green.jpg");
	Texture2D *nullTexture;
	Texture2D *fruitTexture;
	Texture2D *pelletTexture;
	Texture2D *dotTexture;
	Texture2D *borderTexture;


	tile_ptrs tileArr;

	void tileType(char tileChar);

	void readFile(const char * fileName);
	std::vector<char> splitStringToChars(std::string fullString, char delimiter);
	char2d m_board;
};

