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
			starArr[i][j].closedNode = false;
		}
	}
}

void AIPatterns::AStar(glm::vec2 start, glm::vec2 goal, glm::vec2 previous)
{
	if (start == goal)
	{
		m_atGoal = true;
		return;
	}
	if (start != previous)
	{
		//sprite can no longer reverse it's direction from it's previous position
		starArr[static_cast<int>(previous.y)][static_cast<int>(previous.x)].t = '|';
	}
	int xStart = static_cast<int>(start.x);
	int yStart = static_cast<int>(start.y);

	int xGoal = static_cast<int>(goal.x);
	int yGoal = static_cast<int>(goal.y);
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

void AIPatterns::initAStar(Node& start, Node& goal)
{
	std::vector<Node> openList;

	starArr[start.y][start.x].g = 0;
	starArr[start.y][start.x].f = calculateHeuristic(start, goal);
	openList.push_back(starArr[start.y][start.x]);
	while (!openList.empty())
	{
		std::shared_ptr<Node> current = nullptr;
		current = std::make_shared<Node>(openList[0]);
		if (*current == goal)
		{
			constructPath(*current);
			break;
		}
		starArr[current->y][current->x].closedNode = true;
		sortOpenList(openList);
		openList.erase(std::remove(openList.begin(), openList.end(), *current), openList.end());
		for (auto& neighbor : findNeighbors(*current))
		{
			if (neighbor == *current)
			{
				continue;
			}
			bool neighborInClosed = starArr[neighbor.y][neighbor.x].closedNode;
			if (neighborInClosed)
			{
				continue;
			}
			int tentativeG = current->g + calculateHeuristic(*current, neighbor);
			bool neighborInOpen = (std::find(openList.begin(), openList.end(), neighbor) != openList.end());
			if (!neighborInOpen)
			{
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

void AIPatterns::constructPath(Node& current)
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

void AIPatterns::sortOpenList(std::vector<Node>& openlist)
{
	Node temp;
	int n = openlist.size();

	for (int i = n / 2 - 1; i >= 0; i--)
	{
		heapify(openlist, n, i);
	}
	for (int i = n - 1; i >= 0; i--)
	{
		temp = openlist[0];
		openlist[0] = openlist[i];
		openlist[i] = temp;
		heapify(openlist, i, 0);
	}
}

void AIPatterns::heapify(std::vector<Node>& nodes, int size, int index)
{
	Node temp;
	int largest = index;
	int l = 2 * index + 1;
	int r = 2 * index + 2;
	if (l < size && nodes[l].f > nodes[largest].f)
	{
		largest = l;
	}
	if (r < size && nodes[r].f > nodes[largest].f)
	{
		largest = r;
	}
	if (largest != index)
	{
		temp = nodes[0];
		nodes[0] = nodes[index];
		nodes[largest] = temp;
		heapify(nodes, size, largest);
	}
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

int AIPatterns::calculateHeuristic(Node& start, Node& goal)
{
	return abs(start.x - goal.x) + abs(start.y - goal.y);
}

std::vector<Node> AIPatterns::findNeighbors(Node& current)
{
	std::vector<Node> directions(4,current);
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
