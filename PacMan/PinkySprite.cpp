#include "stdafx.h"
#include "PinkySprite.h"


void PinkySprite::moveUp(float deltaTime)
{
	mm_texture = m_textureUp;
	Sprite::moveUp(deltaTime);
}

void PinkySprite::moveDown(float deltaTime)
{
	mm_texture = m_textureDown;
	Sprite::moveDown(deltaTime);
}

void PinkySprite::moveLeft(float deltaTime)
{
	mm_texture = m_textureLeft;
	Sprite::moveLeft(deltaTime);
}

void PinkySprite::moveRight(float deltaTime)
{
	mm_texture = m_textureRight;
	Sprite::moveRight(deltaTime);
}
