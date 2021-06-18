#include "PacWorld.h"

PacWorld::PacWorld(int screenWidth, int screenHeight, float tileLength) :
	m_screenWidth(screenWidth), m_screenHeight(screenHeight), m_tileLength(tileLength)
{
	m_boardMap = std::make_shared<TileMap>("maze.txt", m_tileLength);
	m_originalMap = m_boardMap;


	//pacman
	pacman = std::make_shared<PacManSprite>(m_tileLength, "pac.png", glm::vec2(14, 26), *m_boardMap);
	//AI
	blinky = std::make_shared<BlinkySprite>(m_tileLength, "blinkyright.png", glm::vec2(14, 14), *m_boardMap);
	pinky = std::make_shared<PinkySprite>(m_tileLength, "pinkydown.png", glm::vec2(14, 17), *m_boardMap);
	clyde = std::make_shared<ClydeSprite>(m_tileLength, "clydeup.png", glm::vec2(16, 17), *m_boardMap);
	inky = std::make_shared<InkySprite>(m_tileLength, "inkyup.png", glm::vec2(12, 17), *m_boardMap);

	//original pattern for all AI
	std::shared_ptr<AIPatterns> originalPattern = std::make_shared<AIPatterns>(m_boardMap);
	eDispatcher = std::make_shared<EnemyDispatcher>(originalPattern, blinky, inky, clyde, pinky, m_originalMap);

	//clear tiles to null so nothing is seen visually
	m_boardMap->clearTile(20,9);
	m_boardMap->clearTile(17, 9);
	m_boardMap->clearTile(20, 18);
	m_boardMap->clearTile(17, 18);
	//visuals initalization
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

	pvm = m_projection * m_view * pinky->getModel();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "pvm"), 1, GL_FALSE, &pvm[0][0]);
	pinky->drawSprite();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	pvm = m_projection * m_view * clyde->getModel();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "pvm"), 1, GL_FALSE, &pvm[0][0]);
	clyde->drawSprite();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	pvm = m_projection * m_view * inky->getModel();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "pvm"), 1, GL_FALSE, &pvm[0][0]);
	inky->drawSprite();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void PacWorld::processAI(float deltaTime)
{
	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

	//process modes before dispatcher makes a decision
	processModes(time_span);
	eDispatcher->targetHero(pacman, m_modeAI, deltaTime);
	eDispatcher->collided(pacman);
	t2 = high_resolution_clock::now();
}

void PacWorld::processModes(duration<double>& timePassed)
{
	//method is used case by case in determining how the sprites act on the board overall i.e. frightened, scattered, etc

	switch (m_modeAI)
	{
	case MODE::SCATTER:
		if (timePassed.count() > 7) {
			t1 = high_resolution_clock::now();
			m_modeAI = (m_modeAI == MODE::SCATTER) ? MODE::CHASE : MODE::SCATTER;
		}
		break;
	case MODE::CHASE:
		if (timePassed.count() > 7) {
			t1 = high_resolution_clock::now();
			m_modeAI = (m_modeAI == MODE::SCATTER) ? MODE::CHASE : MODE::SCATTER;
		}
		break;
	case MODE::FRIGHTENED:
		if (timePassed.count() > 7) {
			t1 = high_resolution_clock::now();
			std::cout << "Going to Chase mode" << std::endl;
			eDispatcher->isVulnerable = false;
			m_modeAI = MODE::CHASE;
		}
		break;
	default:
		m_modeAI = MODE::CHASE;
		break;
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

void PacWorld::processCommands(const std::shared_ptr<InputCommand>& command, float deltaTime)
{
	//pacman commands
	if (command)
	{
		dispatcher.playerDispatch(pacman, command, deltaTime);
		eatFood();
	}
}

void PacWorld::eatFood()
{
	int y = static_cast<int>(pacman->getTileIndices().y);
	int x = static_cast<int>(pacman->getTileIndices().x);
	//82 tiles and then release clyde
	if (m_boardMap->getBindedTile(y,x).c_tile == '-' || m_boardMap->getBindedTile(y, x).c_tile == 'a')
	{
		m_boardMap->clearTile(y, x);
		m_score += 1;
	}
	else if (m_boardMap->getBindedTile(y, x).c_tile == 'b')
	{
		m_boardMap->clearTile(y, x);
		m_score += 1;
		m_savedMode = m_modeAI;
		//reset clock so frightened mode starts
		t1 = high_resolution_clock::now();
		std::cout << "Changing Mode" << std::endl;
		eDispatcher->isVulnerable = true;
		m_modeAI = MODE::FRIGHTENED;
	}
	if (m_score == 82)
	{
		eDispatcher->releaseClyde();
		std::cout << "Releasing Clyde" << std::endl;
	}
	if (m_score == 30)
	{
		eDispatcher->releaseInky();
		std::cout << "Releasing Inky" << std::endl;
	}
}