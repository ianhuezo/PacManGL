#pragma once
#include <memory>
#include "TileMap.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <list>
#include <algorithm>


struct Node
{
	int f, g, h, x, y;
	std::shared_ptr<Node> parent;
	char t;
	bool operator == (const Node& n) const { return f == n.f && g == n.g && h == n.h && x == n.x && y == n.y && t == n.t && parent == n.parent; };
	bool operator != (const Node& n) const { return !operator==(n); };
};



class AIPatterns
{
public:
	AIPatterns(std::shared_ptr<TileMap>& map);
	void AStar(glm::vec2 start, glm::vec2 goal);
	int aiCounter = 0;
	~AIPatterns();
private:
	Node starArr[36][28];
	void initAStar(Node start, Node goal);
	void constructPath(Node current);
	int calculateHeuristic(Node start, Node goal);
	bool minF(Node a, Node b);
	std::list<Node> findNeighbors(Node current);


};

