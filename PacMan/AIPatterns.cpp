#include "AIPatterns.h"



AIPatterns::AIPatterns(std::shared_ptr<TileMap>& map)
{
	for (auto i = 0; i < 36; i++)
	{
		for (auto j = 0; j < 28; j++)
		{
			starArr[i][j].f = FLT_MAX;
			starArr[i][j].g = FLT_MAX;
			starArr[i][j].x = j;
			starArr[i][j].y = i;
			starArr[i][j].t = map->getChars()[i][j];
			starArr[i][j].parent = nullptr;
		}
	}
}

void AIPatterns::AStar(glm::vec2 start, glm::vec2 goal)
{
	if (start == goal)
	{
		m_atGoal = true;
		return;
	}
	int xStart = static_cast<int>(start.x);
	int yStart = static_cast<int>(start.y);

	int xGoal = static_cast<int>(goal.x);
	int yGoal = static_cast<int>(goal.y);
	Node startNode = starArr[yStart][xStart];
	Node goalNode = starArr[yGoal][xGoal];
	initAStar(starArr[yStart][xStart], starArr[yGoal][xGoal]);
}


std::list<std::shared_ptr<InputCommand>> AIPatterns::getMovementList()
{
	return m_movementList;
}

bool AIPatterns::atGoal()
{
	return m_atGoal;
}




AIPatterns::~AIPatterns()
{
}

void AIPatterns::initAStar(Node start, Node goal)
{
	std::list<Node> closedList;
	std::list<Node> openList;

	starArr[start.y][start.x].g = 0;
	starArr[start.y][start.x].f = calculateHeuristic(start, goal);
	openList.push_back(starArr[start.y][start.x]);
	while (!openList.empty())
	{
		std::shared_ptr<Node> current = nullptr;
		for (auto node : openList)
		{
			if (current == nullptr || node.f < current->f)
			{
				current = std::make_shared<Node>(node);
			}
		}
		if (*current == goal)
		{
			constructPath(*current);
			break;
		}
		closedList.push_back(*current);
		openList.remove(*current);
		for (auto neighbor : findNeighbors(*current))
		{
			bool neighborInClosed = (std::find(closedList.begin(), closedList.end(), neighbor) != closedList.end());
			if (neighborInClosed)
			{
				continue;
			}
			int tentativeG = current->g + calculateHeuristic(*current, neighbor);
			bool neighborInOpen = (std::find(openList.begin(), openList.end(), neighbor) != openList.end());
			if (!neighborInOpen)
			{
				//std::cout << "Appending neighbor " << neighbor.x << "," << neighbor.y << " " << neighbor.f << " "<< neighbor.g <<std::endl;
				openList.push_back(neighbor);
			}
			else if (tentativeG >= neighbor.g)
			{
				continue;
			}
			starArr[neighbor.y][neighbor.x].parent = current;
			starArr[neighbor.y][neighbor.x].g = tentativeG;
			starArr[neighbor.y][neighbor.x].f = starArr[neighbor.y][neighbor.x].g + calculateHeuristic(neighbor, goal);
		}
	}
}

void AIPatterns::constructPath(Node current)
{
	std::shared_ptr<Node> parent = starArr[current.y][current.x].parent;
	m_movementList.push_back(std::move(createMovementList(starArr[current.y][current.x], *parent)));
	std::shared_ptr<Node> currentMove = nullptr;
	while (starArr[parent->y][parent->x].parent != nullptr)
	{
		currentMove = std::make_shared<Node>(starArr[parent->y][parent->x]);
		parent = starArr[parent->y][parent->x].parent;
		m_movementList.push_back(createMovementList(*currentMove, *parent));
	}
	nextMovement = m_movementList.front();
}

std::shared_ptr<InputCommand> AIPatterns::createMovementList(Node& first, Node& second)
{
	//where current would represent the current enemy tile and next the next tile
	int horizontal = first.x - second.x;
	int vertical = first.y - second.y;

	if (horizontal < 0)
	{
		return std::make_shared<RightCommand>();
	}
	else if (horizontal > 0)
	{
		return std::make_shared<LeftCommand>();
	}
	else if (vertical > 0)
	{
		return std::make_shared<UpCommand>();
	}
	else if (vertical < 0)
	{
		return std::make_shared<DownCommand>();
	}
	else {
		return std::make_shared<StillCommand>();;
	}
}

int AIPatterns::calculateHeuristic(Node start, Node goal)
{
	return abs(start.x - goal.x) + abs(start.y - goal.y);
}

std::list<Node> AIPatterns::findNeighbors(Node current)
{
	std::list<Node> directions;
	//the 4 squares which ghosts cannot move through
	//right
	if (starArr[current.y][current.x + 1].t != '|')
	{
		directions.push_back(starArr[current.y][current.x + 1]);
	}
	//left
	if (starArr[current.y][current.x - 1].t != '|')
	{
		directions.push_back(starArr[current.y][current.x - 1]);
	}
	//down
	if (starArr[current.y + 1][current.x].t != '|' &&
		starArr[current.y + 1][current.x].t != 'a' &&
		starArr[current.y + 1][current.x].t != '=')
	{
		directions.push_back(starArr[current.y + 1][current.x]);
	}
	//up
	if (starArr[current.y - 1][current.x].t != '|')
	{
		directions.push_back(starArr[current.y - 1][current.x]);
	}

	return directions;
}
