#pragma once
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

class Shader
{
public:
	Shader(const char* vertexFile, const char* fragmentFile);
	GLuint ID;
	void use();
private:
	std::string readFile(const char * fileName);
	void compileShader(GLuint shaderType, const char * fileContents, GLuint &shaderID);
	void checkCompileErrors(unsigned int shader, std::string type);
};

