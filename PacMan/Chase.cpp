#include "Chase.h"

Chase::Chase()
{
}

//void Chase::AStar(Node start, Node goal, TileMap& map)
//{
//	std::list<Node> openList;
//	std::list<Node> closedList;
//	openList.push_back(start);
//	start.g = 0;
//	start.f = start.g + calculateHeuristic(start, goal);
//
//	Node current;
//	current = start;
//	int counter = 0;
//	while (counter < 50)
//	{
//		counter++;
//		for (auto node : openList)
//		{
//			if (current.f > node.f)
//			{
//				current = node;
//			}
//		}
//		if (current.x == goal.x && current.y == goal.y)
//		{
//			break;
//		}
//		openList.remove(current);
//		closedList.push_back(current);
//		for (auto neighbor : findNeighbors(current, map))
//		{
//			bool inClosedList = false;
//			for (auto node : closedList)
//			{
//				if (node == neighbor)
//				{
//					inClosedList = true;
//					break;
//				}
//			}
//			if (!inClosedList)
//			{
//				bool inOpenList = false;
//				Node openNeighbor;
//				neighbor.f = neighbor.g + calculateHeuristic(neighbor, goal);
//				for (auto node : openList)
//				{
//					if (neighbor == node)
//					{
//						inOpenList = true;
//						openNeighbor = node;
//						break;
//					}
//				}
//				if (!inOpenList)
//				{
//					openList.push_back(neighbor);
//				}
//				else {
//
//				}
//			}
//		}
//	}
//}
//
//std::list<Node> Chase::findNeighbors(Node current, std::shared_ptr<AIPatterns> pattern)
//{
//	std::list<Node> direction;
//	direction.push_back(current);
//	return direction;
//}
//
//
//int Chase::calculateHeuristic(Node& start, Node& goal)
//{
//	return abs(start.x - goal.x) + abs(start.y - goal.y);
//}

Chase::~Chase()
{
}

std::shared_ptr<InputCommand> AggresiveChase::chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern)
{

	if (startedChase)
	{
		pattern->AStar(enemyAI->getTileIndices(), pacman->getTileIndices());
		startedChase = false;
	}



	if (currentCommand != NULL)
	{
		return currentCommand;
	}
	else
	{
		return std::make_shared<StillCommand>();
	}
}

std::shared_ptr<InputCommand> RandomChase::chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern)
{
	return std::shared_ptr<LeftCommand>();
}

std::shared_ptr<InputCommand> PatrolChase::chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern)
{
	return std::shared_ptr<LeftCommand>();
}

std::shared_ptr<InputCommand> AmbushChase::chase(std::shared_ptr<Sprite> pacman, std::shared_ptr<Sprite> enemyAI, std::shared_ptr<AIPatterns> pattern)
{
	return std::shared_ptr<LeftCommand>();
}

EnemyHandler::EnemyHandler()
{
	enemyChase = std::make_shared<AggresiveChase>();
}
