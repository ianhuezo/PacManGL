#include "stdafx.h"
#include "TileMap.h"


TileMap::TileMap(const char * fileName)
{
	nullTile.assignTexture(*nullTexture);
	fruitTile.assignTexture(*fruitTexture);
	dotTile.assignTexture(*pelletTexture);
	gateTile.assignTexture(*dotTexture);
	borderTile.assignTexture(*borderTexture);

	readFile(fileName);
	updateTileMap();
}

void TileMap::updateTileMap()
{
	std::vector<BindedTile> vec;
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
}




BindedTile TileMap::tileType(char tileChar)
{
	switch (tileChar)
	{
		case TILE::FRUIT:
			return BindedTile(*fruitTexture, fruitTile);
			break;
		case TILE::BORDER:
			return BindedTile(*borderTexture, borderTile);
			break;
		case TILE::PELLET:
			return BindedTile(*pelletTexture, pelletTile);
			break;
		case TILE::DOT:
			return BindedTile(*dotTexture, dotTile);
			break;
		case TILE::GATE:
			return BindedTile(*gateTexture, gateTile);
		case TILE::NILL:
			return BindedTile(*nullTexture, nullTile);
		default:
			return BindedTile(*nullTexture, nullTile);
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
