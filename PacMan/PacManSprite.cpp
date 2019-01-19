#include "PacManSprite.h"

//PacManSprite Specifc up functions(Same as above, just added a texture to the movement)
//UP
void PacManSprite::moveUp(float deltaTime)
{

	mm_texture = m_textureUp;
	Sprite::moveUp(deltaTime);
}
//DOWN
void PacManSprite::moveDown(float deltaTime)
{
	mm_texture = m_textureDown;
	Sprite::moveDown(deltaTime);

}
//LEFT
void PacManSprite::moveLeft(float deltaTime)
{

	mm_texture = m_textureLeft;
	Sprite::moveLeft(deltaTime);
}
//RIGHT
void PacManSprite::moveRight(float deltaTime)
{
	mm_texture = m_textureRight;
	Sprite::moveRight(deltaTime);
}
