#include "PacWorld.h"

PacWorld::PacWorld(int screenWidth, int screenHeight, float tileLength):
	m_screenWidth(screenWidth), m_screenHeight(screenHeight), m_tileLength(tileLength)
{
	m_boardMap = std::make_shared<TileMap>("maze.txt", m_tileLength);
	m_originalMap = m_boardMap;
	pacman = std::make_shared<PacManSprite>(m_tileLength, "pacleft.png", glm::vec2(14, 26), *m_boardMap);
	shader.use();
	glUniform1i(glGetUniformLocation(shader.ID, "mtexture"), 0);
	genTilePVMs();
}

void PacWorld::drawWorld()
{
	for (auto i = 0; i < m_boardMap->getRowSize(); i++) 
	{
		for (auto j = 0; j < m_boardMap->getColSize(); j++)
		{
			auto singlePVM = PVM[i][j];
			m_boardMap->putTile(i, j);
			glUniformMatrix4fv(glGetUniformLocation(shader.ID, "pvm"), 1, GL_FALSE, &singlePVM[0][0]);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}
}

void PacWorld::drawPacMan()
{
	auto pvm = m_projection * m_view * pacman->getModel();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "pvm"), 1, GL_FALSE, &pvm[0][0]);
	pacman->drawSprite();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void PacWorld::processPlayerCommands(std::shared_ptr<InputCommand> command, float deltaTime, InputHandler& handler)
{
	if (command)
	{
		//will store new playerdispatcher command if new ones appears correctly, otherwise keeping the old dispatcher
		if (pacman->checkUp() != '|' && command->command == MOVE::UP && pacman->tileChanged)
		{
			playerDispatcher = command;
		}
		else if (pacman->checkLeft() != '|' && command->command == MOVE::LEFT && pacman->tileChanged)
		{
			playerDispatcher = command;
		}
		else if (pacman->checkRight() != '|' && command->command == MOVE::RIGHT && pacman->tileChanged)
		{
			playerDispatcher = command;
		}
		else if (pacman->checkDown() != '|' && command->command == MOVE::DOWN && pacman->tileChanged)
		{
			playerDispatcher = command;
		}
		//updates pacman movement if the movement is not on a border
		if (pacman->checkUp() != '|' && playerDispatcher->command == MOVE::UP)
		{
			playerDispatcher->execute(*pacman, deltaTime);
		}
		else if (pacman->checkLeft() != '|' && playerDispatcher->command == MOVE::LEFT)
		{
			playerDispatcher->execute(*pacman, deltaTime);
		}
		else if (pacman->checkRight() != '|' && playerDispatcher->command == MOVE::RIGHT)
		{
			playerDispatcher->execute(*pacman, deltaTime);
		}
		else if (pacman->checkDown() != '|' && playerDispatcher->command == MOVE::DOWN)
		{
			playerDispatcher->execute(*pacman, deltaTime);
		}
	}
}


void PacWorld::genTilePVMs()
{
	m_projection = glm::ortho(0.0f, static_cast<float>(m_screenWidth), static_cast<float>(m_screenHeight), 0.0f, -1.0f, 1.0f);
	m_view = glm::mat4(1.0f);
	for (auto i = 0; i < m_boardMap->getRowSize(); i++)
	{
		for (auto j = 0; j < m_boardMap->getColSize(); j++)
		{
			glm::mat4 model;
			float x = m_boardMap->getBindedTile(i, j).position.x;
			float y = m_boardMap->getBindedTile(i, j).position.y;
			model = glm::translate(model, glm::vec3(x, y, 0.0f));
			PVM[i][j] = m_projection * m_view * model;
		}
	}
}