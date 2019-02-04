#include "PacWorld.h"

PacWorld::PacWorld(int screenWidth, int screenHeight, float tileLength):
	m_screenWidth(screenWidth), m_screenHeight(screenHeight), m_tileLength(tileLength)
{
	m_boardMap = std::make_shared<TileMap>("maze.txt", m_tileLength);
	m_originalMap = m_boardMap;


	//AI and pacman
	pacman = std::make_shared<PacManSprite>(m_tileLength, "pacleft.png", glm::vec2(14, 26), *m_boardMap);
	blinky = std::make_shared<Sprite>(m_tileLength, "blinky.png", glm::vec2(14, 14), *m_boardMap);
	blinky->tileChanged = true;
	aStar = std::make_shared<AIPatterns>(m_boardMap);

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

void PacWorld::drawEnemies()
{
	auto pvm = m_projection * m_view * blinky->getModel();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "pvm"), 1, GL_FALSE, &pvm[0][0]);
	blinky->drawSprite();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void PacWorld::processAI(float deltaTime)
{
	blinkyDispatcher = blinkyHandler.handleEnemyInput()->chase(pacman, blinky, aStar);
	dispatcher.blinkyDispatch(blinky, blinkyDispatcher, deltaTime);
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

void PacWorld::processCommands(const std::shared_ptr<InputCommand>& command, float deltaTime)
{
	//pacman commands
	if (command)
	{
		dispatcher.playerDispatch(pacman, command, deltaTime);
		eatFood();
	}
	//enemy commands
}



void PacWorld::eatFood()
{
	if (pacman->checkCurrent() == '-')
	{
		m_boardMap->clearTile(static_cast<int>(pacman->getTileIndices().y),static_cast<int>(pacman->getTileIndices().x));
	}
	else if (pacman->checkCurrent() == 'b')
	{
		m_boardMap->clearTile(static_cast<int>(pacman->getTileIndices().y), static_cast<int>(pacman->getTileIndices().x));
	}
}

