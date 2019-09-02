#include "stdafx.h"
#include "ClydeSprite.h"


void ClydeSprite::moveUp(float deltaTime)
{
	mm_texture = m_textureUp;
	Sprite::moveUp(deltaTime);
}

void ClydeSprite::moveDown(float deltaTime)
{
	mm_texture = m_textureDown;
	Sprite::moveDown(deltaTime);
}

void ClydeSprite::moveLeft(float deltaTime)
{
	mm_texture = m_textureLeft;
	Sprite::moveLeft(deltaTime);
}

void ClydeSprite::moveRight(float deltaTime)
{
	mm_texture = m_textureRight;
	Sprite::moveRight(deltaTime);
}
