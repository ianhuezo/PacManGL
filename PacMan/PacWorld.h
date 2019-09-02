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
#include "EnemyMode.h"
#include "WorldDispatcher.h"
#include "EnemyDispatcher.h"
#include <chrono>

using namespace std::chrono;

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
	void processModes(duration<double>& timePassed);

	void processCommands(const std::shared_ptr<InputCommand>& command, float deltaTime);
	std::shared_ptr<PacManSprite> pacman;
	std::shared_ptr<Sprite> blinky;
	std::shared_ptr<Sprite> pinky;
	std::shared_ptr<Sprite> clyde;
	std::shared_ptr<Sprite> inky;
	Shader shader{ "vertexShader.vs", "fragmentShader.fs" };
private:
	//static variable for points
	int m_score = 0;
	//eating the pellets on the board
	void eatFood();

	WorldDispatcher dispatcher;
	std::shared_ptr<EnemyDispatcher> eDispatcher;
	std::shared_ptr<InputCommand> playerDispatcher = std::make_shared<StillCommand>();

	void genTilePVMs();
	//the current tile map
	std::shared_ptr<TileMap> m_boardMap;
	//store original settings in map for future reference i.e. next level
	std::shared_ptr<TileMap> m_originalMap;
	//screen width/height for world
	int m_screenWidth;
	int m_screenHeight;
	int m_modeAI = MODE::CHASE;
	int m_savedMode = -1;
	float m_tileLength;

	//clocks to measure the game state
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	glm::vec2 m_mapPixel[ROW_SIZE][COL_SIZE];
	glm::mat4 m_projection;
	glm::mat4 m_view;
	glm::mat4 PVM[ROW_SIZE][COL_SIZE];
};

