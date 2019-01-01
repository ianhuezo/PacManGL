#include "Sprite.h"


Sprite::Sprite(float tileLength, const char * filePath, glm::vec2(indices))
	:m_tileLength(tileLength), m_model(glm::mat4(1.0f)),m_texture(NULL), m_indices(indices)
{
	m_model = glm::translate(m_model, glm::vec3(tileLength * 14, tileLength * 26, 0.0f));
	m_texture = new Texture2D(filePath);
}

Sprite::~Sprite()
{
	delete m_texture;
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
//Pacman Specific movements
void PacMan::moveUp()
{
	m_texture = new Texture2D("pacup.png");
	m_model = glm::translate(m_model, glm::vec3(0, -0.5, 0.0f));
}

void PacMan::moveDown()
{
	m_texture = new Texture2D("pacdown.png");
	m_model = glm::translate(m_model, glm::vec3(0, 0.5, 0.0f));
}

void PacMan::moveLeft()
{
	m_texture = new Texture2D("pacleft.png");
	m_model = glm::translate(m_model, glm::vec3(-0.5, 0, 0.0f));
}

void PacMan::moveRight()
{
	m_texture = new Texture2D("pacright.png");
	m_model = glm::translate(m_model, glm::vec3(0.5, 0, 0.0f));
}
