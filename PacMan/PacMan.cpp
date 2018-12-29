// PacManGL.cpp : Defines the entry point for the console application.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>
#include "TileMap.h"
#include "Shader.h"

GLint WIDTH = 540;
GLint HEIGHT = 700;
float ratio;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

//http://www.gamasutra.com/view/feature/3938/the_pacman_dossier.php?print=1 - a good explanation of the pacman game
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	auto window = glfwCreateWindow(WIDTH, HEIGHT, "Pac Man", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//Initialize the pacman board components
	Shader shader("vertexShader.vs", "fragmentShader.fs");
	//pacman maze gotten from https://www.pandadeath.com/uploads/3/0/7/5/30753079/maze.txt
	//the number of tiles for pacman
	//36 rows, 28 cols for pacman. First 4 rows are nothing, last 3 rows are nothing
	float tileNum = 28 * 36;
	float tileLength = sqrt(ceil((WIDTH*HEIGHT) / tileNum));
	float vertices[] = {
		0.0f,       tileLength,  0.0f,   0, 1,// Top-left
		tileLength, tileLength,  0.0f,   1, 1, // Top-right
		tileLength, 0.0f,        0.0f,   1, 0.0f,// Bottom-right
		0.0f,       0.0f,        0.0f,   0.0f, 0  // Bottom-left
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	GLuint vbo, vao, ebo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
	//TextureLoader t1;
	//TextureLoader t2;
	//t1.genTexture("container.jpg");
	//t2.genTexture("bluetile.jpg");
	TileMap map("maze.txt");
	shader.use();
	glUniform1i(glGetUniformLocation(shader.ID, "mtexture"), 80);

	//
	auto projection = glm::ortho(0.0f, static_cast<float>(WIDTH), static_cast<float>(HEIGHT), 0.0f, -1.0f, 1.0f);
	auto view = glm::mat4(1.0f);
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		// render
		// ------
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();
		glBindVertexArray(vbo);

		int rowNum = 0;
		int colNum = 0;
		for (auto row : map.getMap())
		{
			for (auto col : row)
			{
				glm::mat4 model;
				model = glm::translate(model, glm::vec3(tileLength*colNum, tileLength * rowNum, 0.0f));
				auto pvm = projection * view * model;
				glUniformMatrix4fv(glGetUniformLocation(shader.ID, "pvm"), 1, GL_FALSE, &pvm[0][0]);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			}
			rowNum += 1;
			colNum = 0;
		}
		rowNum = 0;

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	ratio = static_cast<float>(width) / static_cast<float>(height);
}

