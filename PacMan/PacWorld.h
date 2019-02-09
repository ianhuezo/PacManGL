#pragma once
#include "TileMap.h"
#include "Sprite.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include "InputCommand.h"
#include "PacManSprite.h"
#include "WorldDispatcher.h"
#include "Chase.h"
#include "AIPatterns.h"
#include <utility>
//#include PacAudio.h eventual class that may be implemented here
//#include 
class PacWorld
{
public:
	PacWorld(int screenWidth, int screenHeight, float tileLength);
	void drawWorld();
	void drawPacMan();
	void drawEnemies();
	void processAI(float deltaTime);

	void processCommands(const std::shared_ptr<InputCommand>& command, float deltaTime);
	std::shared_ptr<PacManSprite> pacman;
	std::shared_ptr<Sprite> blinky;
	Shader shader{ "vertexShader.vs", "fragmentShader.fs" };
private:
	void eatFood();


	WorldDispatcher dispatcher;
	std::shared_ptr<InputCommand> playerDispatcher = std::make_shared<StillCommand>();
	std::shared_ptr<InputCommand> blinkyDispatcher = std::make_shared<StillCommand>();
	EnemyHandler blinkyHandler;

	std::shared_ptr<AIPatterns> aStar = nullptr;
	std::shared_ptr<AIPatterns> originalAI = nullptr;
	bool blinkyAIOn = false;
	

	void genTilePVMs();
	//the current tile map
	std::shared_ptr<TileMap> m_boardMap;
	//store original settings in map for future reference i.e. next level
	std::shared_ptr<TileMap> m_originalMap;
	//screen width/height for world
	int m_screenWidth;
	int m_screenHeight;

	float m_tileLength;
	bool m_moveExecuted = false;
	int currentState = 1;
	glm::vec2 m_mapPixel[ROW_SIZE][COL_SIZE];
	glm::mat4 m_projection;
	glm::mat4 m_view;
	glm::mat4 PVM[ROW_SIZE][COL_SIZE];
};

