#include "PacSprite.h"

PacSprite::~PacSprite()
{
}

PacSprite::PacSprite(glm::mat4 initPosition)
{
	m_model = initPosition;
}
