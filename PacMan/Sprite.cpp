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

void Sprite::moveUp(float deltaTime)
{
	if (movementEnabled)
	{
		mm_pixelPosition.y -= 100.0f*deltaTime;
		m_model = glm::translate(m_model, glm::vec3(0, -100.0f*deltaTime, 0.0f));
		if (abs(mm_pixelPosition.y - mm_fixedPosition.y) >= m_tileLength)
		{
			m_indices.y--;
			int row = m_indices.x;
			int col = m_indices.y;
			mm_fixedPosition = tilePositions[row][col];
			std::cout << m_indices.x << std::endl;
		}
	}
}

void Sprite::moveDown(float deltaTime)
{
	if (movementEnabled)
	{
		mm_pixelPosition.y += 100.0f*deltaTime;
		m_model = glm::translate(m_model, glm::vec3(0, 100.0f*deltaTime, 0.0f));
		if (abs(mm_pixelPosition.y - mm_fixedPosition.y) >= m_tileLength)
		{
			m_indices.y++;
			int row = m_indices.x;
			int col = m_indices.y;
			mm_fixedPosition = tilePositions[row][col];
			std::cout << m_indices.y << std::endl;

		}
	}
}

void Sprite::moveRight(float deltaTime)
{
	if (movementEnabled)
	{
		mm_pixelPosition.x += 100.0f*deltaTime;
		m_model = glm::translate(m_model, glm::vec3(100.0f*deltaTime, 0, 0.0f));
		if (abs(mm_pixelPosition.x - mm_fixedPosition.x) >= m_tileLength)
		{
			m_indices.x++;
			int row = m_indices.x;
			int col = m_indices.y;
			mm_fixedPosition = tilePositions[row][col];
			std::cout << m_indices.x << std::endl;

		}
	}
}

void Sprite::moveLeft(float deltaTime)
{
	if (movementEnabled)
	{
		mm_pixelPosition.x -= 100.0f*deltaTime;
		m_model = glm::translate(m_model, glm::vec3(-100.0f*deltaTime, 0, 0.0f));
		if (abs(mm_pixelPosition.x - mm_fixedPosition.x) >= m_tileLength)
		{
			m_indices.x--;
			int row = m_indices.x;
			int col = m_indices.y;
			mm_fixedPosition = tilePositions[row][col];
			std::cout << m_indices.x << std::endl;

		}
	}
}
PacMan::~PacMan()
{

}
//Pacman Specific movements
void PacMan::moveUp(float deltaTime)
{
	if (movementEnabled)
	{
		mm_pixelPosition.y -= 100.0f * deltaTime;
		m_texture = m_textureUp;
		m_model = glm::translate(m_model, glm::vec3(0, -100.0f * deltaTime, 0.0f));
		if (abs(mm_pixelPosition.y - mm_fixedPosition.y) >= m_tileLength)
		{
			m_indices.y--;
			int row = m_indices.x;
			int col = m_indices.y;
			mm_fixedPosition = tilePositions[row][col];
			std::cout << m_indices.y << std::endl;
		}
	}
}

void PacMan::moveDown(float deltaTime)
{
	if (movementEnabled)
	{
		mm_pixelPosition.y += 100.0f * deltaTime;
		m_texture = m_textureDown;
		m_model = glm::translate(m_model, glm::vec3(0, 100.0f * deltaTime, 0.0f));
		if (abs(mm_pixelPosition.y - mm_fixedPosition.y) >= m_tileLength)
		{
			m_indices.y++;
			int row = m_indices.x;
			int col = m_indices.y;
			mm_fixedPosition = tilePositions[row][col];
			std::cout << m_indices.y << std::endl;

		}
	}
}

void PacMan::moveLeft(float deltaTime)
{
	if (movementEnabled)
	{
		mm_pixelPosition.x -= 100.0f * deltaTime;
		m_texture = m_textureLeft;
		m_model = glm::translate(m_model, glm::vec3(-100.0f*deltaTime, 0, 0.0f));
		if (abs(mm_pixelPosition.x - mm_fixedPosition.x) >= m_tileLength)
		{
			m_indices.x--;
			int row = m_indices.x;
			int col = m_indices.y;
			mm_fixedPosition = tilePositions[row][col];
			std::cout << m_indices.x << std::endl;

		}
	}
}

void PacMan::moveRight(float deltaTime)
{
	if (movementEnabled)
	{
		mm_pixelPosition.x += 100.0f * deltaTime;
		m_texture = m_textureRight;
		m_model = glm::translate(m_model, glm::vec3(100.0f * deltaTime, 0, 0.0f));
		if (abs(mm_pixelPosition.x - mm_fixedPosition.x) >= m_tileLength)
		{
			m_indices.x++;
			int row = m_indices.x;
			int col = m_indices.y;
			mm_fixedPosition = tilePositions[row][col];
			std::cout << m_indices.x << std::endl;

		}
	}
}
