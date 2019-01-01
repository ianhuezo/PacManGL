#include "Sprite.h"


Sprite::Sprite(float tileLength, const char * filePath, glm::vec2(indices))
	:m_tileLength(tileLength), m_model(glm::mat4(1.0f)),m_texture(std::make_shared<Texture2D>(filePath)), m_indices(indices)
{
	m_model = glm::translate(m_model, glm::vec3(tileLength * 14, tileLength * 26, 0.0f));
}

Sprite::~Sprite()
{

}

void Sprite::drawSprite()
{
	m_texture->assignTexture();
}

void Sprite::moveUp()
{
	m_model = glm::translate(m_model, glm::vec3(0, -0.5, 0.0f));
}

void Sprite::moveDown()
{
	m_model = glm::translate(m_model, glm::vec3(0, 0.5, 0.0f));
}

void Sprite::moveRight()
{
	m_model = glm::translate(m_model, glm::vec3(0.5, 0, 0.0f));
}

void Sprite::moveLeft()
{
	m_model = glm::translate(m_model, glm::vec3(-0.5, 0, 0.0f));
}
PacMan::~PacMan()
{

}
//Pacman Specific movements
void PacMan::moveUp()
{
	m_texture = m_textureUp;
	m_model = glm::translate(m_model, glm::vec3(0, -0.5, 0.0f));
}

void PacMan::moveDown()
{
	m_texture = m_textureDown;
	m_model = glm::translate(m_model, glm::vec3(0, 0.5, 0.0f));
}

void PacMan::moveLeft()
{
	m_texture = m_textureLeft;
	m_model = glm::translate(m_model, glm::vec3(-0.5, 0, 0.0f));
}

void PacMan::moveRight()
{
	m_texture = m_textureRight;
	m_model = glm::translate(m_model, glm::vec3(0.5, 0, 0.0f));
}
