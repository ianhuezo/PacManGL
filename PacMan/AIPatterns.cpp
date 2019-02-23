#include "AIPatterns.h"



AIPatterns::AIPatterns(std::shared_ptr<TileMap>& map)
{
	for (auto i = 0; i < 36; i++)
	{
		for (auto j = 0; j < 28; j++)
		{
			starArr[i][j].f = FLT_MAX;
			starArr[i][j].g = FLT_MAX;
			starArr[i][j].h = 0;
			starArr[i][j].x = j;
			starArr[i][j].y = i;
			starArr[i][j].t = map->getChars()[i][j];
			starArr[i][j].parent = nullptr;
		}
	}
}

void AIPatterns::AStar(glm::vec2 start, glm::vec2 goal)
{
	int xStart = static_cast<int>(start.x);
	int yStart = static_cast<int>(start.y);

	int xGoal = static_cast<int>(goal.x);
	int yGoal = static_cast<int>(goal.y);
	//the check for when the bot will collide or may collide with pacman
	if ((abs(xStart - xGoal) + abs(yStart - yGoal)) <= 1)
	{
		if (xStart - xGoal > 0)
		{
			nextMovement = std::make_shared<LeftCommand>();
		}
		else if (xStart - xGoal < 0)
		{
			nextMovement = std::make_shared<RightCommand>();
		}
		else if (yStart - yGoal < 0)
		{
			nextMovement = std::make_shared<DownCommand>();
		}
		else if (yStart - yGoal > 0)
		{
			nextMovement = std::make_shared<UpCommand>();
		}
		else
		{
			nextMovement = std::make_shared<StillCommand>();
		}
		return;
	}
	Node startNode = starArr[yStart][xStart];
	Node goalNode = starArr[yGoal][xGoal];
	initAStar(starArr[yStart][xStart], starArr[yGoal][xGoal]);
}



AIPatterns::~AIPatterns()
{
}

void AIPatterns::initAStar(Node start, Node goal)
{
	std::list<Node> closedList;
	std::list<Node> openList;

	starArr[start.y][start.x].g = 0;
	starArr[start.y][start.x].f = calculateHeuristic(start,goal);
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
	std::shared_ptr<Node> nextMove = nullptr;
	while (starArr[parent->y][parent->x].parent != nullptr)
	{
		nextMove = std::make_shared<Node>(starArr[parent->y][parent->x]);
		//if a minigoal is found save it and execute that instead of going for pacman directly
		parent = starArr[parent->y][parent->x].parent;
	}
	int horizontal = nextMove->x - parent->x;
	int vertical = nextMove->y - parent->y;
	if (horizontal > 0)
	{
		nextMovement = std::make_shared<RightCommand>();
	}
	else if (horizontal < 0)
	{
		nextMovement = std::make_shared<LeftCommand>();
	}
	else if (vertical > 0)
	{
		nextMovement = std::make_shared<DownCommand>();
	}
	else if (vertical < 0)
	{
		nextMovement = std::make_shared<UpCommand>();
	}
	else {
		nextMovement = std::make_shared<StillCommand>();
		m_stopAI = true;
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
	if (starArr[current.y + 1][current.x].t != '|')
	{
		directions.push_back(starArr[current.y + 1][current.x]);
	}
	//up
	if (starArr[current.y - 1][current.x].t != '|' &&
		starArr[current.y - 1][current.x].t != 'a' && starArr[current.y - 1][current.x].t != '=')
	{
		directions.push_back(starArr[current.y - 1][current.x]);
	}

	return directions;
}
