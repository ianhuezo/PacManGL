#include "PacWorld.h"

PacWorld::PacWorld(int screenWidth, int screenHeight, float tileLength) :
	m_screenWidth(screenWidth), m_screenHeight(screenHeight), m_tileLength(tileLength)
{
	m_boardMap = std::make_shared<TileMap>("maze.txt", m_tileLength);
	m_originalMap = m_boardMap;


	//pacman
	pacman = std::make_shared<PacManSprite>(m_tileLength, "pacleft.png", glm::vec2(14, 26), *m_boardMap);
	//AI
	blinky = std::make_shared<Sprite>(m_tileLength, "blinky.png", glm::vec2(14, 14), *m_boardMap);
	pinky = std::make_shared<Sprite>(m_tileLength, "pinky.png", glm::vec2(12, 14), *m_boardMap);
	clyde = std::make_shared<Sprite>(m_tileLength, "clyde.png", glm::vec2(13, 14), *m_boardMap);
	inky = std::make_shared<Sprite>(m_tileLength, "inky.png", glm::vec2(15, 14), *m_boardMap);

	//blinky patterns
	m_blinkyAIPatterns = std::make_shared<AIPatterns>(m_boardMap);
	m_blinkyChase = std::make_shared<AggresiveChase>();
	m_blinkyScatter = std::make_shared<TopRightScatter>();

	//Pinky patterns
	m_pinkyAIPatterns = std::make_shared<AIPatterns>(m_boardMap);
	m_pinkyChase = std::make_shared<AmbushChase>();
	m_pinkyScatter = std::make_shared<TopLeftScatter>();

	//clyde patterns
	m_clydeAIPatterns = std::make_shared<AIPatterns>(m_boardMap);
	m_clydeChase = std::make_shared<PatrolChase>();
	m_clydeScatter = std::make_shared<BotLeftScatter>();

	//inky patterns
	m_inkyAIPatterns = std::make_shared<AIPatterns>(m_boardMap);
	m_inkyChase = std::make_shared<RandomChase>();
	m_inkyScatter = std::make_shared<BotRightScatter>();

	//assign an empty pattern so that all AI can reference it for A* algorithm
	m_originalAI = m_blinkyAIPatterns;
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
	resetAIPatterns();
	if (pacman->pacmanIsHit(*blinky))
	{
		blinky->resetSprite();
		return;
	}
	useChase(deltaTime);
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
	if (pacman->checkCurrent() == '-' || pacman->checkCurrent() == 'a' || pacman->checkCurrent() == '+')
	{
		m_boardMap->clearTile(static_cast<int>(pacman->getTileIndices().y), static_cast<int>(pacman->getTileIndices().x));
	}
	else if (pacman->checkCurrent() == 'b')
	{
		m_boardMap->clearTile(static_cast<int>(pacman->getTileIndices().y), static_cast<int>(pacman->getTileIndices().x));
	}
}

void PacWorld::resetAIPatterns()
{
	//enemy patterns being reset for each  sprite

	//blinky
	m_blinkyAIPatterns = std::make_shared<AIPatterns>(*m_originalAI);
	//pinky
	m_pinkyAIPatterns = std::make_shared<AIPatterns>(*m_originalAI);
	//clyde
	m_clydeAIPatterns = std::make_shared<AIPatterns>(*m_originalAI);
	//inky
	m_inkyAIPatterns = std::make_shared<AIPatterns>(*m_originalAI);
}

void PacWorld::useScatter(float deltaTime)
{
	m_blinkyScatter->scatter(pacman, blinky, m_blinkyAIPatterns, deltaTime);
	m_pinkyScatter->scatter(pacman, pinky, m_pinkyAIPatterns, deltaTime);
	m_clydeScatter->scatter(pacman, clyde, m_clydeAIPatterns, deltaTime);
	m_inkyScatter->scatter(pacman, inky, m_inkyAIPatterns, deltaTime);
}

void PacWorld::useChase(float deltaTime)
{
	//important to keep blinky for inky for code to execute correctly in order
	m_blinkyChase->chase(pacman, blinky, nullptr,m_blinkyAIPatterns, m_originalMap, deltaTime);

	m_inkyChase->chase(pacman, inky, blinky,m_inkyAIPatterns, m_originalMap, deltaTime);

	m_pinkyChase->chase(pacman, pinky, nullptr,m_pinkyAIPatterns, m_originalMap, deltaTime);

	m_clydeChase->chase(pacman, clyde, nullptr,m_clydeAIPatterns, m_originalMap, deltaTime);
}

