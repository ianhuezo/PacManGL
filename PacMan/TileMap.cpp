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
	m_rows = tileArr.size();
	m_cols = tileArr[0].size();
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
	originalArr = tileArr;
}

void TileMap::clearTile(int row, int col)
{
	tileArr[row][col] = BindedTile(*nullTexture, nullTile,'-');
	putTile(row, col);
}

void TileMap::putTile(int row, int col)
{
	try {
		tileArr[row][col].tile.assignTexture(tileArr[row][col].texture);
	}
	catch (int e)
	{
		std::cout<<"The index is out of range for the vector with error code : "<< e << std::endl;
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
			return BindedTile(*fruitTexture, fruitTile, tileChar);
			break;
		case TILE::BORDER:
			return BindedTile(*borderTexture, borderTile, tileChar);
			break;
		case TILE::PELLET:
			return BindedTile(*pelletTexture, pelletTile, tileChar);
			break;
		case TILE::DOT:
			return BindedTile(*dotTexture, dotTile,tileChar);
			break;
		case TILE::GATE:
			return BindedTile(*gateTexture, gateTile,tileChar);
		case TILE::NILL:
			return BindedTile(*nullTexture, nullTile,tileChar);
		default:
			return BindedTile(*nullTexture, nullTile,tileChar);
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
