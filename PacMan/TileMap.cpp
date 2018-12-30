#include "stdafx.h"
#include "TileMap.h"


TileMap::TileMap(const char * fileName)
{
	nullTexture.textureImage("blue.jpg");
	borderTexture.textureImage("green.jpg");
	readFile(fileName);
	updateTileMap();
}

void TileMap::updateTileMap()
{

}


TileMap::~TileMap()
{
}


void TileMap::tileType(char tileChar)
{
	if (tileChar == '|')
	{
		borderTile.setTexture(borderTexture);
	}
	else {
		borderTile.setTexture(nullTexture);
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
