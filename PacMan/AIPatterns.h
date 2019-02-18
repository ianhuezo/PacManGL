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


struct Node
{
	int f, g, h, x, y;
	std::shared_ptr<Node> parent;
	char t;
	bool operator == (const Node& n) const {return x == n.x && y == n.y ; };
	bool operator != (const Node& n) const { return !operator==(n); };
};



class AIPatterns
{
public:
	AIPatterns(std::shared_ptr<TileMap>& map);
	void AStar(glm::vec2 start, glm::vec2 goal);
	std::shared_ptr<InputCommand> nextMovement;
	bool m_stopAI = false;
	~AIPatterns();
private:
	Node starArr[36][28];
	void initAStar(Node start, Node goal);
	void constructPath(Node current);
	int calculateHeuristic(Node start, Node goal);
	std::list<Node> findNeighbors(Node current);
	


};

