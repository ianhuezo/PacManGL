#include "PacWorld.h"

PacWorld::PacWorld(int screenWidth, int screenHeight, float tileLength):
	m_screenWidth(screenWidth), m_screenHeight(screenHeight), m_tileLength(tileLength)
{
	m_boardMap = std::make_shared<TileMap>("maze.txt");
	m_originalMap = m_boardMap;
	pacman = std::make_shared<PacMan>(m_tileLength, "pacleft.png", glm::vec2(14, 26));
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

void PacWorld::processPlayerCommands(std::shared_ptr<InputCommand> command, float deltaTime)
{
	if (command)
	{
		if (!collisionDetect(command->x, command->y))
		{
			command->execute(*pacman, deltaTime);
		}
		
		//if (pacman->commandCounter <= 1 && !collisionDetect(command->x, command->y))
		//{
		//	std::cout << "case 1" << std::endl;
		//	std::cout << pacman->commandCounter << std::endl;
		//	std::cout << !collisionDetect(command->x, command->y) << std::endl;
		//	std::cout << !collisionDetect(currentCommand->x, currentCommand->y) << std::endl << std::endl;

		//	prevCommand = currentCommand;
		//	currentCommand = command;
		//	currentCommand->execute(*pacman, deltaTime);
		//	currentState = 1;
		//}

		//else if (!collisionDetect(currentCommand->x, currentCommand->y) && pacman->commandCounter >= 1)
		//{
		//	std::cout << "case 2" << std::endl;
		//	std::cout << pacman->commandCounter << std::endl;
		//	std::cout << !collisionDetect(command->x, command->y) << std::endl;
		//	std::cout << !collisionDetect(currentCommand->x, currentCommand->y) << std::endl << std::endl;
		//	prevCommand = currentCommand;
		//	currentCommand->execute(*pacman, deltaTime);
		//	currentState = 4;
		//}
		//else if (pacman->commandCounter > 1)
		//{
		//	currentCommand = prevCommand;
		//	prevCommand->execute(*pacman, deltaTime);
		//}
		//else {
		//	std::cout << "case 3" << std::endl;
		//	std::cout << pacman->commandCounter << std::endl;
		//	std::cout << !collisionDetect(command->x, command->y) << std::endl;
		//	std::cout << !collisionDetect(currentCommand->x, currentCommand->y) << std::endl << std::endl;

		//	prevCommand = currentCommand;
		//	pacman->commandCounter = 0;
		//	currentState = 4;
		//}
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
			m_mapPixel[i][j] = glm::vec2(m_tileLength*j, m_tileLength*i);
			model = glm::translate(model, glm::vec3(m_tileLength*j, m_tileLength * i, 0.0f));
			PVM[i][j] = m_projection * m_view * model;
		}
	}
}

bool PacWorld::collisionDetect(int inX, int inY)
{
	glm::vec2 pacIndices = pacman->getTileIndices();
	//rows are y, cols are x
	int row = pacIndices.y + inY;

	int col = pacIndices.x + inX;
	//top left corner of each sprite tile
	glm::vec2 rect1 = pacman->getModelPosition();
	//currently in the top left corner of each  game tile
	glm::vec2 rect2 = glm::vec2(m_mapPixel[row][col].x, m_mapPixel[row][col].y);
	char somechar = m_boardMap->getChars()[row][col];
	//std::cout << somechar << std::endl;
	bool badchar = (somechar == 'g' || somechar == '|');
	//std::cout << "Next tile is: " << somechar << std::endl;
	//std::cout << rect1.x << std::endl;
	//std::cout << rect2.x << std::endl << std::endl;
	if (rect1.x <= rect2.x + m_tileLength &&
		rect1.x + m_tileLength >= rect2.x &&
		rect1.y <= m_tileLength + rect2.y &&
		rect1.y + m_tileLength >= rect2.y &&
		badchar) {
		return true;
	}
	else {
		return false;
	}

}
