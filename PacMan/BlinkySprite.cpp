#include "stdafx.h"
#include "BlinkySprite.h"


void BlinkySprite::moveUp(float deltaTime)
{
	mm_texture = m_textureUp;
	Sprite::moveUp(deltaTime);
}

void BlinkySprite::moveDown(float deltaTime)
{
	mm_texture = m_textureDown;
	Sprite::moveDown(deltaTime);
}

void BlinkySprite::moveLeft(float deltaTime)
{
	mm_texture = m_textureLeft;
	Sprite::moveLeft(deltaTime);
}

void BlinkySprite::moveRight(float deltaTime)
{
	mm_texture = m_textureRight;
	Sprite::moveRight(deltaTime);
}
