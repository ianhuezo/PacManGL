#include "Shader.h"

Shader::Shader(const char * vertexFile, const char * fragmentFile)
{
	//open files for the shader
	GLuint vertexID;
	GLuint fragmentID;
	std::string vertexContents = readFile(vertexFile);
	std::string fragmentContents = readFile(fragmentFile);
	compileShader(GL_VERTEX_SHADER, vertexContents.c_str(),vertexID);
	checkCompileErrors(vertexID, "VERTEX");
	compileShader(GL_FRAGMENT_SHADER, fragmentContents.c_str(),fragmentID);
	checkCompileErrors(fragmentID, "FRAGMENT");
	ID = glCreateProgram();
	glAttachShader(ID, vertexID);
	glAttachShader(ID, fragmentID);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");
	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
}

std::string Shader::readFile(const char * fileName)
{
	std::ifstream file(fileName);
	std::string fileString;
	std::string output;
	while (std::getline(file, fileString))
	{
		output += fileString;
		output.push_back('\n');
	}
	file.close();
	return output;
}
void Shader::use()
{
	glUseProgram(ID);
}

void Shader::compileShader(GLuint shaderType, const char * fileContents, GLuint &shaderID)
{
	GLuint shader = glCreateShader(shaderType);
	GLint isCompiled = 0;
	glShaderSource(shader, 1, &fileContents, 0);
	glCompileShader(shader);
	shaderID = shader;
}

void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}

