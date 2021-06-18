#pragma once
#include <chrono>
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

class PacManSprite : public Sprite
{
public:
	PacManSprite(float tileLength, const char * filePath, glm::vec2(indices), TileMap& charMap) :
		Sprite(tileLength, filePath, glm::vec2(indices), charMap) {}
	virtual void moveUp(float deltaTime);
	virtual void moveDown(float deltaTime);
	virtual void moveLeft(float deltaTime);
	virtual void moveRight(float deltaTime);
private:
	void switchAnimation(int direction, int& stage);
	float createFrameBuffer(float time, int numTimes);
	int FRAME_TIME = 4;
	//mouth of pacman stage
	enum STAGE {
		CLOSED,
		OPENING,
		CLOSING,
		WIDE
	};
	//directions of pacman
	enum DIRECTION {
		UP,
		LEFT,
		DOWN,
		RIGHT
	};

	int m_stage = STAGE::CLOSED;
	float m_time = 0;
	//regular pacman
	std::shared_ptr<Texture2D> m_textureUp = std::make_shared<Texture2D>("pacup1.png");
	std::shared_ptr<Texture2D> m_textureDown = std::make_shared<Texture2D>("pacdown1.png");
	std::shared_ptr<Texture2D> m_textureLeft = std::make_shared<Texture2D>("pacleft1.png");
	std::shared_ptr<Texture2D> m_textureRight = std::make_shared<Texture2D>("pacright1.png");
	//wider mouth pacman
	std::shared_ptr<Texture2D> m_textureUp2 = std::make_shared<Texture2D>("pacup2.png");
	std::shared_ptr<Texture2D> m_textureDown2 = std::make_shared<Texture2D>("pacdown2.png");
	std::shared_ptr<Texture2D> m_textureLeft2 = std::make_shared<Texture2D>("pacleft2.png");
	std::shared_ptr<Texture2D> m_textureRight2 = std::make_shared<Texture2D>("pacright2.png");
	//pacman as a yellow ball
	std::shared_ptr<Texture2D> m_textureball = std::make_shared<Texture2D>("pac.png");

	//pacman animation stage, will switch off depending on time
	std::shared_ptr<Texture2D> m_animationStage = std::make_shared<Texture2D>("pac.png");
};

