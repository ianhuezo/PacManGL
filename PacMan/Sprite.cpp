#include "Sprite.h"

Sprite::Sprite(float tileLength, const char * filePath, glm::vec2(indices), TileMap& charMap)
	:mm_tileLength(tileLength), mm_model(glm::mat4(1.0f)), mm_texture(std::make_shared<Texture2D>(filePath)), mm_indices(indices), charMap(charMap)
{
	int row = mm_indices.y;
	int col = mm_indices.x;
	mm_pixelPosition = charMap.getBindedTile(row,col).position;
	mm_fixedPosition = mm_pixelPosition;
	mm_halfTileLength = mm_tileLength / 2;
	mm_model = glm::translate(mm_model, glm::vec3(mm_pixelPosition.x, mm_pixelPosition.y, 0.0f));
}

void Sprite::drawSprite()
{
	mm_texture->assignTexture();
}

//Function does the general move for each direction
void Sprite::generalMove(float& pixelPosition, float& fixedPosition, float& index, float& deltaTime, float number)
{
	//need to reverse for tiles :)
	pixelPosition = pixelPosition + (number*spriteSpeed*deltaTime);
	if (abs(pixelPosition - fixedPosition) > (mm_tileLength))
	{
		tileChanged = true;
		index = index + number;
		int row = mm_indices.y;
		int col = mm_indices.x;
		mm_fixedPosition = charMap.getBindedTile(row,col).position;
	}

}

//UP
void Sprite::moveUp(float deltaTime)
{
	mm_model = glm::translate(mm_model, glm::vec3(0, -spriteSpeed * deltaTime, 0.0f));
	generalMove(mm_pixelPosition.y, mm_fixedPosition.y, mm_indices.y, deltaTime, -1);
}
//DOWN
void Sprite::moveDown(float deltaTime)
{
	mm_model = glm::translate(mm_model, glm::vec3(0, spriteSpeed*deltaTime, 0.0f));
	generalMove(mm_pixelPosition.y, mm_fixedPosition.y, mm_indices.y, deltaTime, 1);
}
//RIGHT
void Sprite::moveRight(float deltaTime)
{
	mm_model = glm::translate(mm_model, glm::vec3(spriteSpeed*deltaTime, 0, 0.0f));
	generalMove(mm_pixelPosition.x, mm_fixedPosition.x, mm_indices.x, deltaTime, 1);
}
//LEFT
void Sprite::moveLeft(float deltaTime)
{
	mm_model = glm::translate(mm_model, glm::vec3(-spriteSpeed * deltaTime, 0, 0.0f));
	generalMove(mm_pixelPosition.x, mm_fixedPosition.x, mm_indices.x, deltaTime, -1);
}

void Sprite::moveStill(float deltaTime)
{

}


char Sprite::checkLeft()
{
	return charMap.getBindedTile(mm_indices.y,mm_indices.x - 1).c_tile;
}

char Sprite::checkRight()
{
	return charMap.getBindedTile(mm_indices.y, mm_indices.x + 1).c_tile;
}

char Sprite::checkUp()
{
	return charMap.getBindedTile(mm_indices.y - 1, mm_indices.x).c_tile;
}

char Sprite::checkDown()
{
	 return charMap.getBindedTile(mm_indices.y + 1, mm_indices.x).c_tile;
}
