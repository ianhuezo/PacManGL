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
#include <vector>
#include "InputCommand.h"
#include "PacWorld.h"
#include <iostream>
#include <thread>
#include <chrono>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

GLint WIDTH = 540;
GLint HEIGHT = 700;
float ratio;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processPlayer(GLFWwindow* window, InputHandler& inputHandler, PacWorld& world);
void update_fps_counter(GLFWwindow* window);
void processInput(GLFWwindow* window);

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;
InputCommand* currentCommand;

bool gameStarted = false;

//http://www.gamasutra.com/view/feature/3938/the_pacman_dossier.php?print=1 - a good explanation of the pacman game
//https://dev.to/code2bits/pac-man-patterns--ghost-movement-strategy-pattern-1k1a - how the ghosts move
//http://www.free80sarcade.com/pacman.php - actual pacman game


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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Initialize the pacman board components
	//Shader shader("vertexShader.vs", "fragmentShader.fs");
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
	//glBindVertexArray(0);
	//TileMap map("maze.txt");
	//shader.use();
	//glUniform1i(glGetUniformLocation(shader.ID, "mtexture"), 0);

	//
	//auto projection = glm::ortho(0.0f, static_cast<float>(WIDTH), static_cast<float>(HEIGHT), 0.0f, -1.0f, 1.0f);
	//auto view = glm::mat4(1.0f);
	PacWorld pacWorld(WIDTH, HEIGHT, tileLength);
	InputHandler inputHandler(window);
	
	//PacMan pacman(tileLength, "pacright.png", glm::vec2(14, 26));
	//auto counter = 0;
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(window);
		processPlayer(window, inputHandler, pacWorld);
		// render
		// ------
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		pacWorld.shader.use();
		pacWorld.drawWorld();
		pacWorld.drawEnemies();
		pacWorld.drawPacMan();
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

void processPlayer(GLFWwindow* window, InputHandler& inputHandler, PacWorld& world)
{
	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS || gameStarted == true)
	{
		gameStarted = true;
		std::shared_ptr<InputCommand> command = inputHandler.handleKeyInput();
		world.processCommands(command, deltaTime);
		world.processAI(deltaTime);
	}
	
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//void update_fps_counter(GLFWwindow* window)
//{
//	double current_seconds = glfwGetTime();
//	elapsed_seconds = current_seconds - previous_seconds;
//	if (elapsed_seconds > 0.25)
//	{
//		previous_seconds = current_seconds;
//		float fps = (float)frame_count / elapsed_seconds;
//		//std::cout << fps << std::endl;
//		frame_count = 0;
//	}
//	frame_count++;
//}

