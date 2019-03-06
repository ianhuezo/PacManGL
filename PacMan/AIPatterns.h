#pragma once
#include <memory>
#include "TileMap.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <list>
#include <algorithm>
#include "InputCommand.h"
#include "Sprite.h"
#include <iostream>
#include <vector>


struct Node
{
	int f, g, x, y;
	std::shared_ptr<Node> parent;
	char t;
	bool closedNode;
	bool operator == (const Node& n) const { return x == n.x && y == n.y; };
	bool operator != (const Node& n) const { return !operator==(n); };
};



class AIPatterns
{
public:
	AIPatterns(std::shared_ptr<TileMap>& map);
	void AStar(glm::vec2 start, glm::vec2 goal, glm::vec2 previous);
	std::list<std::shared_ptr<InputCommand>> getMovementList();
	bool atGoal();
	std::shared_ptr<InputCommand> nextMovement;
	~AIPatterns();
private:
	Node starArr[36][28];
	void initAStar(Node& start, Node& goal);
	void constructPath(Node& current);
	void sortOpenList(std::vector<Node>& openlist);
	void heapify(std::vector<Node>& nodes, int size, int index);
	std::shared_ptr<InputCommand> createMovementList(Node& first, Node& second);

	bool m_atGoal = false;
	std::list<std::shared_ptr<InputCommand>> m_movementList;
	int calculateHeuristic(Node& start, Node& goal);
	std::list<Node> findNeighbors(Node& current);
};

