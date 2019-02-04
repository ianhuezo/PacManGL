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

	start.g = 0;
	start.f = 0;
	openList.push_back(start);
	
	Node current = start;

	int counter = 0;
	while (!openList.empty())
	{
		counter++;
		for (auto node : openList)
		{
			if (node.f <= current.f)
			{
				//std::cout << node.x << "," << node.y << std::endl;
				current = node;
			}
		}
		//std::cout << "Appending neighbor " << current.x << "," << current.y << " " << current.f << " " << current.g << std::endl;
		if (current.x == goal.x && current.y == goal.y)
		{
			break;
		}
		openList.remove(current);
		closedList.push_back(current);
		for (auto neighbor : findNeighbors(current))
		{
			bool neighborInClosed = (std::find(closedList.begin(), closedList.end(), neighbor) != closedList.end());
			if (neighborInClosed)
			{
				continue;
			}
			int tentativeG = current.g + calculateHeuristic(current, neighbor);
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
			starArr[neighbor.y][neighbor.x].parent = std::make_shared<Node>(current);
			starArr[neighbor.y][neighbor.x].g = tentativeG;
			starArr[neighbor.y][neighbor.x].f = starArr[neighbor.y][neighbor.x].g + calculateHeuristic(neighbor, goal);
		}
	}

}

int AIPatterns::calculateHeuristic(Node start, Node goal)
{
	return abs(start.x - goal.x) + abs(start.y - goal.y);
}

bool AIPatterns::minF(Node a, Node b)
{
	return (a.f < b.f);
}

std::list<Node> AIPatterns::findNeighbors(Node current)
{
	std::list<Node> directions;
	//right
	if (starArr[current.y][current.x + 1].t != '|' && starArr[current.y][current.x + 1].t != 'g')
	{
		directions.push_back(starArr[current.y][current.x + 1]);
	}
	//left
	if (starArr[current.y][current.x - 1].t != '|' && starArr[current.y][current.x - 1].t != 'g')
	{
		directions.push_back(starArr[current.y][current.x - 1]);
	}
	//down
	if (starArr[current.y + 1][current.x].t != '|' && starArr[current.y + 1][current.x].t != 'g')
	{
		directions.push_back(starArr[current.y + 1][current.x]);
	}
	//up
	if (starArr[current.y - 1][current.x].t != '|' && starArr[current.y - 1][current.x].t != 'g')
	{
		directions.push_back(starArr[current.y - 1][current.x]);
	}

	return directions;
}
