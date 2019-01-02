#include "Sprite.h"


Sprite::Sprite(float tileLength, const char * filePath, glm::vec2(indices))
	:m_tileLength(tileLength), m_model(glm::mat4(1.0f)),m_texture(std::make_shared<Texture2D>(filePath)), m_indices(indices)
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

void Sprite::updateIndices()
{

}

void Sprite::moveUp()
{
	if (movementEnabled)
	{
		mm_pixelPosition.y -= 0.5;
		m_model = glm::translate(m_model, glm::vec3(0, -0.5, 0.0f));
	}
}

void Sprite::moveDown()
{
	if (movementEnabled)
	{
		mm_pixelPosition.y += 0.5;
		m_model = glm::translate(m_model, glm::vec3(0, 0.5, 0.0f));
	}
}

void Sprite::moveRight()
{
	if (movementEnabled)
	{
		mm_pixelPosition.x += 0.5;
		m_model = glm::translate(m_model, glm::vec3(0.5, 0, 0.0f));
	}
}

void Sprite::moveLeft()
{
	if (movementEnabled)
	{
		mm_pixelPosition.x -= 0.5;
		m_model = glm::translate(m_model, glm::vec3(-0.5, 0, 0.0f));
	}
}
PacMan::~PacMan()
{

}
//Pacman Specific movements
void PacMan::moveUp()
{
	if (movementEnabled)
	{
		mm_pixelPosition.y -= 0.5;
		m_texture = m_textureUp;
		m_model = glm::translate(m_model, glm::vec3(0, -0.5, 0.0f));
		if (abs(mm_pixelPosition.y - mm_fixedPosition.y) >= m_tileLength)
		{
			m_indices.y--;
			int row = m_indices.x;
			int col = m_indices.y;
			mm_fixedPosition = tilePositions[row][col];
		}
	}
}

void PacMan::moveDown()
{
	if (movementEnabled)
	{
		mm_pixelPosition.y += 0.5;
		m_texture = m_textureDown;
		m_model = glm::translate(m_model, glm::vec3(0, 0.5, 0.0f));
		if (abs(mm_pixelPosition.y - mm_fixedPosition.y) >= m_tileLength)
		{
			m_indices.y++;
			int row = m_indices.x;
			int col = m_indices.y;
			mm_fixedPosition = tilePositions[row][col];

		}
	}
}

void PacMan::moveLeft()
{
	if (movementEnabled)
	{
		mm_pixelPosition.x -= 0.5;
		m_texture = m_textureLeft;
		m_model = glm::translate(m_model, glm::vec3(-0.5, 0, 0.0f));
		if (abs(mm_pixelPosition.x - mm_fixedPosition.x) >= m_tileLength)
		{
			m_indices.x--;
			int row = m_indices.x;
			int col = m_indices.y;
			mm_fixedPosition = tilePositions[row][col];

		}
	}
}

void PacMan::moveRight()
{
	if (movementEnabled)
	{
		mm_pixelPosition.x += 0.5;
		m_texture = m_textureRight;
		m_model = glm::translate(m_model, glm::vec3(0.5, 0, 0.0f));
		if (abs(mm_pixelPosition.x - mm_fixedPosition.x) >= m_tileLength)
		{
			m_indices.x++;
			int row = m_indices.x;
			int col = m_indices.y;
			mm_fixedPosition = tilePositions[row][col];

		}
	}
}
