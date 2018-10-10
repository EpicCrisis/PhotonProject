
#include <iostream>
#include "MyPhoton.h"
#include <Windows.h>
#include <gl/GLU.h>
#include <GLFW/glfw3.h>
#include "Application.h"
#include <ctime>

const int RESOLUTION_X = 800;
const int RESOLUTION_Y = 600;

void OnWindowResized(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//! Use ortho2D view
	gluOrtho2D(0, width, 0, height);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Controls(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_ESCAPE)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}
}

float tick = 0.0f;
float tickRate = 0.01f;

void UpdateGame(float deltaTime)
{
	Application::Instance().Update(deltaTime);

	tick -= deltaTime;

	if (tick <= 0.0f)
	{
		tick = tickRate;
		//system("CLS");
		//std::cout << "Delta Time : " << deltaTime << " | ";
		//std::cout << "FPS : " << 1.0f / deltaTime << " | ";
		//std::cout << "Time : " << Application::Instance().time << std::endl;
	}
}

static void cursor_position_callback(GLFWwindow* window, double xPos, double yPos)
{
	if (Application::Instance().network != NULL)
	{
		int myID = 4201;
		Application::Instance().SetMousePos(xPos, yPos - RESOLUTION_Y);
		Application::Instance().network->sendEvent(myID, xPos, yPos - RESOLUTION_Y);
	}
}

bool bVSync = true;
float lastUpdateTime = 0.0f;
float deltaTime = 0.0f;
float FPS = 0.0f;

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create m_a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(RESOLUTION_X, RESOLUTION_Y, "Photon Multiplayer Project", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// Make the window's context current.
	glfwMakeContextCurrent(window);
	// Adjust VSync.
	glfwSwapInterval(bVSync ? 1 : 0);
	// Set ortho view.
	OnWindowResized(window, RESOLUTION_X, RESOLUTION_Y);
	// Check for windows change size.
	glfwSetWindowSizeCallback(window, OnWindowResized);
	// Check for input keys.
	glfwSetKeyCallback(window, Controls);
	// Return the position of the cursor position.
	glfwSetCursorPosCallback(window, cursor_position_callback);
	// Run application start.
	Application::Instance().Start();

	while (!glfwWindowShouldClose(window))
	{
		// Render here,
		glClear(GL_COLOR_BUFFER_BIT);

		// Calculate delta time and FPS.
		deltaTime = (float)glfwGetTime() - lastUpdateTime;
		lastUpdateTime = (float)glfwGetTime();
		FPS = 1.0f / deltaTime;

		UpdateGame(deltaTime);
		Application::Instance().Draw();
	
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}