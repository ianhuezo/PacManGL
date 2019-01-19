#include "stdafx.h"
#include "TileMap.h"


TileMap::TileMap(const char * fileName, float tileLength)
{
	nullTile.assignTexture(*nullTexture);
	fruitTile.assignTexture(*fruitTexture);
	dotTile.assignTexture(*pelletTexture);
	gateTile.assignTexture(*dotTexture);
	borderTile.assignTexture(*borderTexture);

	m_tileLength = tileLength;
	readFile(fileName);
	updateTileMap();
	m_rows = tileArr.size();
	m_cols = tileArr[0].size();
}

void TileMap::updateTileMap()
{
	std::vector<BindedTile> vec;
	int i = 0;
	int j = 0;
	for (auto row : m_board)
	{
		vec.clear();
		for (auto col : row)
		{
			glm::vec2 position = glm::vec2(m_tileLength*j, m_tileLength*i);
			vec.push_back(tileType(col,position));
			j++;
		}
		j = 0;
		i++;
		tileArr.push_back(vec);
	}
	originalArr = tileArr;
}

void TileMap::clearTile(int row, int col)
{
	tileArr[row][col] = BindedTile(*nullTexture, nullTile,'-',tileArr[row][col].position);
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




BindedTile TileMap::tileType(char tileChar, glm::vec2 position)
{
	switch (tileChar)
	{
		case TILE::FRUIT:
			return BindedTile(*fruitTexture, fruitTile, tileChar,position);
			break;
		case TILE::BORDER:
			return BindedTile(*borderTexture, borderTile, tileChar, position);
			break;
		case TILE::PELLET:
			return BindedTile(*pelletTexture, pelletTile, tileChar, position);
			break;
		case TILE::DOT:
			return BindedTile(*dotTexture, dotTile, tileChar, position);
			break;
		case TILE::GATE:
			return BindedTile(*gateTexture, gateTile, tileChar, position);
		case TILE::NILL:
			return BindedTile(*nullTexture, nullTile, tileChar, position);
		default:
			return BindedTile(*nullTexture, nullTile, tileChar, position);
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
