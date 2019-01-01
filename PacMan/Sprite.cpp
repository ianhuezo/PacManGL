#include "Sprite.h"


Sprite::Sprite(glm::mat4 initPosition)
	:m_model(initPosition)
{
	
}

Sprite::~Sprite()
{
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
