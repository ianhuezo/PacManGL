#pragma once
#include <iostream>
class Sprite
{
public:
	Sprite();
	~Sprite();
	void moveUp() {
		std::cout << "Moving Up" << std::endl;
	}
	void moveDown() {
		std::cout << "Moving Down" << std::endl;
	}
	void moveRight() {
		std::cout << "Moving Right" << std::endl;
	}
	void moveLeft() {
		std::cout << "Moving Left" << std::endl;
	}
};

