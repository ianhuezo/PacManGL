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
void Sprite::generalMove(float& pixelPosition, float& fixedPosition, float& index, const float& velocity, float indexNum)
{
	//need to reverse for tiles :)
	pixelPosition = pixelPosition + velocity;
	if (abs(pixelPosition - fixedPosition) > (mm_tileLength))
	{
		tileChanged = true;
		index = index + indexNum;
		int row = mm_indices.y;
		int col = mm_indices.x;
		mm_fixedPosition = charMap.getBindedTile(row,col).position;
	}
	else {
		tileChanged = false;
	}
}

//UP
void Sprite::moveUp(float deltaTime)
{
	float velocity = -spriteSpeed * deltaTime;
	mm_model = glm::translate(mm_model, glm::vec3(0, velocity, 0.0f));
	generalMove(mm_pixelPosition.y, mm_fixedPosition.y, mm_indices.y, velocity, -1.0f);
}
//DOWN
void Sprite::moveDown(float deltaTime)
{
	float velocity = spriteSpeed * deltaTime;
	mm_model = glm::translate(mm_model, glm::vec3(0, velocity, 0.0f));
	generalMove(mm_pixelPosition.y, mm_fixedPosition.y, mm_indices.y, velocity, 1);
}
//RIGHT
void Sprite::moveRight(float deltaTime)
{
	float velocity = spriteSpeed * deltaTime;
	mm_model = glm::translate(mm_model, glm::vec3(velocity, 0, 0.0f));
	generalMove(mm_pixelPosition.x, mm_fixedPosition.x, mm_indices.x, velocity, 1);
}
//LEFT
void Sprite::moveLeft(float deltaTime)
{
	float velocity = -spriteSpeed * deltaTime;
	mm_model = glm::translate(mm_model, glm::vec3(velocity, 0, 0.0f));
	generalMove(mm_pixelPosition.x, mm_fixedPosition.x, mm_indices.x, velocity, -1);
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
