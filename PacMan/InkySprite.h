#pragma once
#include "Sprite.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Texture2D.h"
#include <memory>
#include <iostream>
#include <math.h>
#include "TileMap.h"

class InkySprite : public Sprite
{
public:
	InkySprite(float tileLength, const char * filePath, glm::vec2(indices), TileMap& charMap) :
		Sprite(tileLength, filePath, glm::vec2(indices), charMap) {}
	virtual void moveUp(float deltaTime);
	virtual void moveDown(float deltaTime);
	virtual void moveLeft(float deltaTime);
	virtual void moveRight(float deltaTime);
private:
	std::shared_ptr<Texture2D> m_textureUp = std::make_shared<Texture2D>("inkyup.png");
	std::shared_ptr<Texture2D> m_textureDown = std::make_shared<Texture2D>("inkydown.png");
	std::shared_ptr<Texture2D> m_textureLeft = std::make_shared<Texture2D>("inkyleft.png");
	std::shared_ptr<Texture2D> m_textureRight = std::make_shared<Texture2D>("inkyright.png");
};