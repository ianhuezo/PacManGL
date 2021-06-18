#include "PacManSprite.h"

//PacManSprite Specifc up functions(Same as above, just added a texture to the movement)
//UP
void PacManSprite::moveUp(float deltaTime)
{
	if (m_time <= 0) {
		m_time = createFrameBuffer(deltaTime, FRAME_TIME);
		switchAnimation(DIRECTION::UP, m_stage);
	}
	m_time -= deltaTime;
	mm_texture = m_animationStage;
	Sprite::moveUp(deltaTime);
}
//DOWN
void PacManSprite::moveDown(float deltaTime)
{
	if (m_time <= 0) {
		m_time = createFrameBuffer(deltaTime, FRAME_TIME);
		switchAnimation(DIRECTION::DOWN, m_stage);
	}
	m_time -= deltaTime;
	mm_texture = m_animationStage;
	Sprite::moveDown(deltaTime);

}
//LEFT
void PacManSprite::moveLeft(float deltaTime)
{
	if (m_time <= 0) {
		m_time = createFrameBuffer(deltaTime, FRAME_TIME);
		switchAnimation(DIRECTION::LEFT, m_stage);
	}
	m_time -= deltaTime;
	mm_texture = m_animationStage;
	Sprite::moveLeft(deltaTime);
}
//RIGHT
void PacManSprite::moveRight(float deltaTime)
{
	if (m_time <= 0) {
		m_time = createFrameBuffer(deltaTime, FRAME_TIME);
		switchAnimation(DIRECTION::RIGHT, m_stage);
	}
	m_time -= deltaTime;
	mm_texture = m_animationStage;
	Sprite::moveRight(deltaTime);
}

void PacManSprite::switchAnimation(int direction, int& stage)
{
	switch (direction) {
		case DIRECTION::UP:
			switch (stage) {
			case STAGE::CLOSED:
				m_animationStage = m_textureball;
				stage = STAGE::OPENING;
				break;
			case STAGE::OPENING:
				m_animationStage = m_textureUp;
				stage = STAGE::WIDE;
				break;
			case STAGE::CLOSING:
				m_animationStage = m_textureUp;
				stage = STAGE::CLOSED;
				break;
			case STAGE::WIDE:
				m_animationStage = m_textureUp2;
				stage = STAGE::CLOSING;
				break;
			}
			break;
		case DIRECTION::DOWN:
			switch (stage) {
			case STAGE::CLOSED:
				m_animationStage = m_textureball;
				stage = STAGE::OPENING;
				break;
			case STAGE::OPENING:
				m_animationStage = m_textureDown;
				stage = STAGE::WIDE;
				break;
			case STAGE::CLOSING:
				m_animationStage = m_textureDown;
				stage = STAGE::CLOSED;
				break;
			case STAGE::WIDE:
				m_animationStage = m_textureDown2;
				stage = STAGE::CLOSING;
				break;
			}
			break;
		case DIRECTION::LEFT:
			switch (stage) {
			case STAGE::CLOSED:
				m_animationStage = m_textureball;
				stage = STAGE::OPENING;
				break;
			case STAGE::OPENING:
				m_animationStage = m_textureLeft;
				stage = STAGE::WIDE;
				break;
			case STAGE::CLOSING:
				m_animationStage = m_textureLeft;
				stage = STAGE::CLOSED;
				break;
			case STAGE::WIDE:
				m_animationStage = m_textureLeft2;
				stage = STAGE::CLOSING;
				break;
			}
			break;
		case DIRECTION::RIGHT:
			switch (stage) {
			case STAGE::CLOSED:
				m_animationStage = m_textureball;
				stage = STAGE::OPENING;
				break;
			case STAGE::OPENING:
				m_animationStage = m_textureRight;
				stage = STAGE::WIDE;
				break;
			case STAGE::CLOSING:
				m_animationStage = m_textureRight;
				stage = STAGE::CLOSED;
				break;
			case STAGE::WIDE:
				m_animationStage = m_textureRight2;
				stage = STAGE::CLOSING;
				break;
			}
			break;
		}
}

float PacManSprite::createFrameBuffer(float time, int numTimes)
{
	while (numTimes > -1) {
		time += time;
		numTimes -= 1;
	}
	return time;
}
