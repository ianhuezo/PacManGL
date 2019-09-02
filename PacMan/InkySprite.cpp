#include "stdafx.h"
#include "InkySprite.h"


void InkySprite::moveUp(float deltaTime)
{
	mm_texture = m_textureUp;
	Sprite::moveUp(deltaTime);
}

void InkySprite::moveDown(float deltaTime)
{
	mm_texture = m_textureDown;
	Sprite::moveDown(deltaTime);
}

void InkySprite::moveLeft(float deltaTime)
{
	mm_texture = m_textureLeft;
	Sprite::moveLeft(deltaTime);
}

void InkySprite::moveRight(float deltaTime)
{
	mm_texture = m_textureRight;
	Sprite::moveRight(deltaTime);
}
