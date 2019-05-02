#include "Sprite.h"

Sprite::Sprite(float tileLength, const char * filePath, glm::vec2(indices), TileMap& charMap)
	:mm_tileLength(tileLength), mm_model(glm::mat4(1.0f)), mm_texture(std::make_shared<Texture2D>(filePath)), mm_indices(indices), charMap(charMap)
{
	int row = mm_indices.y;
	int col = mm_indices.x;
	mm_pixelPosition = charMap.getBindedTile(row,col).position;
	mm_fixedPosition = mm_pixelPosition;
	int tunnelRow = 17;
	int tunnelLeft = 0;
	int tunnelRight = 27;
	rightTunnel = charMap.getBindedTile(tunnelRow, tunnelRight).position;
	leftTunnel = charMap.getBindedTile(tunnelRow, tunnelLeft).position;

	tunnelPositionLeft = glm::translate(tunnelPositionLeft, glm::vec3(leftTunnel.x, leftTunnel.y, 0.0f));
	tunnelPositionRight = glm::translate(tunnelPositionRight, glm::vec3(rightTunnel.x, rightTunnel.y, 0.0f));
	mm_halfTileLength = mm_tileLength / 2;
	mm_model = glm::translate(mm_model, glm::vec3(mm_pixelPosition.x, mm_pixelPosition.y, 0.0f));
	mm_filepath = filePath;
	mm_charMap = std::make_shared <TileMap>(charMap);
	mm_initialPosition = indices;
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
		index = index + indexNum;
		if (mm_indices.x == 0 && this->spriteDirection == MOVE::LEFT)
		{
			mm_indices.x = 26;
		}
		if (mm_indices.x == 27 && this->spriteDirection == MOVE::RIGHT)
		{
			mm_indices.x = 1;
		}
		if (mm_indices.x < 6 && mm_indices.y == 17 || mm_indices.x > 22 && mm_indices.y == 17)
		{
			m_inTunnel = true;
		}
		else {
			m_inTunnel = false;
		}
		int row = mm_indices.y;
		int col = mm_indices.x;
		mm_fixedPosition = charMap.getBindedTile(row,col).position;
		tileChanged = true;
	}
	else{
		tileChanged = false;
	}
}

//UP
void Sprite::moveUp(float deltaTime)
{
	spriteDirection = MOVE::UP;
	float velocity = -spriteSpeed * deltaTime;
	mm_model = glm::translate(mm_model, glm::vec3(0, velocity, 0.0f));
	generalMove(mm_pixelPosition.y, mm_fixedPosition.y, mm_indices.y, velocity, -1.0f);
}
//DOWN
void Sprite::moveDown(float deltaTime)
{
	spriteDirection = MOVE::DOWN;
	float velocity = spriteSpeed * deltaTime;
	mm_model = glm::translate(mm_model, glm::vec3(0, velocity, 0.0f));
	generalMove(mm_pixelPosition.y, mm_fixedPosition.y, mm_indices.y, velocity, 1);
}
//RIGHT
void Sprite::moveRight(float deltaTime)
{
	spriteDirection = MOVE::RIGHT;
	float velocity = spriteSpeed * deltaTime;
	if (mm_pixelPosition.x >= rightTunnel.x && this->spriteDirection == MOVE::RIGHT)
	{
		mm_pixelPosition.x = leftTunnel.x;
		mm_model = glm::translate(tunnelPositionLeft, glm::vec3(velocity, 0, 0.0f));
	}
	mm_model = glm::translate(mm_model, glm::vec3(velocity, 0, 0.0f));
	generalMove(mm_pixelPosition.x, mm_fixedPosition.x, mm_indices.x, velocity, 1);
}
//LEFT
void Sprite::moveLeft(float deltaTime)
{
	spriteDirection = MOVE::LEFT;
	float velocity = -spriteSpeed * deltaTime;
	if (mm_pixelPosition.x <= 0 && this->spriteDirection == MOVE::LEFT)
	{
		mm_pixelPosition.x = rightTunnel.x;
		mm_model = glm::translate(tunnelPositionRight, glm::vec3(velocity, 0, 0.0f));
	}
	mm_model = glm::translate(mm_model, glm::vec3(velocity, 0, 0.0f));
	generalMove(mm_pixelPosition.x, mm_fixedPosition.x, mm_indices.x, velocity, -1);
}

void Sprite::moveStill(float deltaTime)
{
	spriteDirection = MOVE::STILL;
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

char Sprite::checkCurrent()
{
	return charMap.getBindedTile(mm_indices.y, mm_indices.x).c_tile;
}

void Sprite::resetSprite()
{
	*this = Sprite(mm_tileLength,mm_filepath, mm_initialPosition, *mm_charMap);
}

bool Sprite::pacmanIsHit(const Sprite & enemy)
{
	if (glm::abs(enemy.mm_pixelPosition - this->mm_pixelPosition).x < mm_halfTileLength &&
		glm::abs(enemy.mm_pixelPosition - this->mm_pixelPosition).y < mm_halfTileLength)
	{
		return true;
	}
	else {
		return false;
	}
}






