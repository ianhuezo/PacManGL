#include "PacWorld.h"

PacWorld::PacWorld(int screenWidth, int screenHeight, float tileLength):
	m_screenWidth(screenWidth), m_screenHeight(screenHeight), m_tileLength(tileLength)
{
	m_boardMap = std::make_shared<TileMap>("maze.txt");
	m_originalMap = m_boardMap;
	pacman = std::make_shared<PacMan>(m_tileLength, "pacright.png", glm::vec2(14, 26));
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

void PacWorld::genTilePVMs()
{
	m_projection = glm::ortho(0.0f, static_cast<float>(m_screenWidth), static_cast<float>(m_screenHeight), 0.0f, -1.0f, 1.0f);
	m_view = glm::mat4(1.0f);
	for (auto i = 0; i < m_boardMap->getRowSize(); i++)
	{
		for (auto j = 0; j < m_boardMap->getColSize(); j++)
		{
			glm::mat4 model;
			model = glm::translate(model, glm::vec3(m_tileLength*j, m_tileLength * i, 0.0f));
			PVM[i][j] = m_projection * m_view * model;
		}
	}
}

void PacWorld::collisionDetect(int inX, int inY)
{
	glm::vec2 pacIndices = pacman->getTileIndices();
	bool goodRight = (m_boardMap->getChars()[pacIndices.x + inX][pacIndices.y + inY] != '|');
	std::cout << m_boardMap->getChars()[pacIndices.x + inX][pacIndices.y + inY] << std::endl;
}
