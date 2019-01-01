#pragma once
#include "stb_image.h"
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <string>
class Texture2D
{
public:
	GLuint ID;
	Texture2D(const char * filePath);
	void assignTexture() {glBindTexture(GL_TEXTURE_2D, this->ID); };
	//disable copy constructor
	//Texture2D(const Texture2D&) = delete;
	
};

