#include "Sprite.h"


Sprite::Sprite(float tileLength, const char * filePath, glm::vec2(indices))
	:m_tileLength(tileLength), m_model(glm::mat4(1.0f)), m_texture(std::make_shared<Texture2D>(filePath)), m_indices(indices)
{
	for (int i = 0; i < ROW_SIZE; i++)
	{
		for (int j = 0; j < COL_SIZE; j++)
		{
			tilePositions[i][j] = glm::vec2(m_tileLength * i, m_tileLength * j);
		}
	}
	mm_pixelPosition = tilePositions[14][26];
	mm_fixedPosition = mm_pixelPosition;
	m_model = glm::translate(m_model, glm::vec3(mm_pixelPosition.x, mm_pixelPosition.y, 0.0f));
}

void Sprite::drawSprite()
{
	m_texture->assignTexture();
}


//Function does the general move for each direction
void Sprite::generalMove(float& pixelPosition, float& fixedPosition, float& index, float& deltaTime, float number)
{
	pixelPosition = pixelPosition + (number*spriteSpeed*deltaTime);
	if (abs(pixelPosition - fixedPosition) >= m_tileLength)
	{
		index = index + number;
		int row = m_indices.x;
		int col = m_indices.y;
		mm_fixedPosition = tilePositions[row][col];
		std::cout << index << std::endl;
	}
}
//UP
void Sprite::moveUp(float deltaTime)
{
	m_model = glm::translate(m_model, glm::vec3(0, -spriteSpeed*deltaTime, 0.0f));
	generalMove(mm_pixelPosition.y, mm_fixedPosition.y, m_indices.y, deltaTime, -1);
}
//DOWN
void Sprite::moveDown(float deltaTime)
{

	m_model = glm::translate(m_model, glm::vec3(0, spriteSpeed*deltaTime, 0.0f));
	generalMove(mm_pixelPosition.y, mm_fixedPosition.y, m_indices.y, deltaTime, 1);
}
//RIGHT
void Sprite::moveRight(float deltaTime)
{
	m_model = glm::translate(m_model, glm::vec3(spriteSpeed*deltaTime, 0, 0.0f));
	generalMove(mm_pixelPosition.x, mm_fixedPosition.x, m_indices.x, deltaTime, 1);
}
//LEFT
void Sprite::moveLeft(float deltaTime)
{
	m_model = glm::translate(m_model, glm::vec3(-spriteSpeed*deltaTime, 0, 0.0f));
	generalMove(mm_pixelPosition.x, mm_fixedPosition.x, m_indices.x, deltaTime, -1);
}


//PACMAN Specifc up functions(Same as above, just added a texture to the movement
//UP
void PacMan::moveUp(float deltaTime)
{
	if (movementEnabled)
	{
		m_texture = m_textureUp;
		Sprite::moveUp(deltaTime);
	}
}
//DOWN
void PacMan::moveDown(float deltaTime)
{
	if (movementEnabled)
	{
		m_texture = m_textureDown;
		Sprite::moveDown(deltaTime);
	}
}
//LEFT
void PacMan::moveLeft(float deltaTime)
{
	if (movementEnabled)
	{
		m_texture = m_textureLeft;
		Sprite::moveLeft(deltaTime);
	}
}
//RIGHT
void PacMan::moveRight(float deltaTime)
{
	if (movementEnabled)
	{
		m_texture = m_textureRight;
		Sprite::moveRight(deltaTime);
	}
}