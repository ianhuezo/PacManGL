#include "stdafx.h"
#include "TileMap.h"


TileMap::TileMap(const char * fileName)
{
	nullTexture = new Texture2D("black.jpg");
	fruitTexture = new Texture2D("green.jpg");
	pelletTexture = new Texture2D("green.jpg");
	dotTexture = new Texture2D("green.jpg");

	nullTile.setTexture(*nullTexture);
	readFile(fileName);
	updateTileMap();
}

void TileMap::updateTileMap()
{
	std::vector<Tiles> vec;
	for (auto row : m_board)
	{
		vec.clear();
		for (auto col : row)
		{
			vec.push_back(tileType(col));
		}
		tileArr.push_back(vec);
	}
}


TileMap::~TileMap()
{
	delete nullTexture;
	delete pelletTexture;
	delete dotTexture;
	delete fruitTexture;
}



Tiles TileMap::tileType(char tileChar)
{
	switch (tileChar)
	{
		case TILE::FRUIT:
			return nullTile;
			break;
		case TILE::PELLET:
			return pelletTile;
			break;
		case TILE::DOT:
			return dotTile;
			break;
		case TILE::GATE:
			return gateTile;
			break;
		case TILE::BORDER:
			return  borderTile;
			break;
		case TILE::NILL:
			return nullTile;
			break;
		default:
			return nullTile;
	}
}

void TileMap::readFile(const char * fileName)
{
	std::ifstream file(fileName);
	std::string fileString;
	std::string output;
	std::vector<char> row;
	while (std::getline(file, fileString))
	{
		output += fileString;
		row = splitStringToChars(fileString, ' ');
		m_board.push_back(row);
	}
}



std::vector<char> TileMap::splitStringToChars(std::string fullString, char delimiter)
{
	std::vector<char> vecTiles;
	for (auto& mychar : fullString)
	{
		if (mychar != delimiter)
		{
			vecTiles.push_back(mychar);
		}
	}
	return vecTiles;
}
