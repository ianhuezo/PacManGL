#pragma once
#include "TileMap.h"
#include "Sprite.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
//#include PacAudio.h eventual class that may be implemented here
//#include 
class PacWorld
{
public:
	PacWorld(int screenWidth, int screenHeight, float tileLength);
	void drawWorld();
	void drawPacMan();
	std::shared_ptr<PacMan> pacman;
	Shader shader{ "vertexShader.vs", "fragmentShader.fs" };
	~PacWorld();
private:

	void genTilePVMs();
	//the current tile map
	std::shared_ptr<TileMap> m_boardMap;
	//store original settings in map for future reference i.e. next level
	std::shared_ptr<TileMap> m_originalMap;
	//screen width/height for world
	int m_screenWidth;
	int m_screenHeight;

	float m_tileLength;

	glm::mat4 m_projection;
	glm::mat4 m_view;
	glm::mat4 PVM[ROW_SIZE][COL_SIZE];

};

