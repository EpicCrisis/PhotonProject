
#include <iostream>
#include "MyPhoton.h"
#include <Windows.h>
#include <gl/GLU.h>
#include <GLFW/glfw3.h>
#include "Application.h"
#include <ctime>

const int RESOLUTION_X = 800;
const int RESOLUTION_Y = 600;

float tick = 0.0f;
float tickRate = 0.01f;

bool bVSync = true;
float lastUpdateTime = 0.0f;
float deltaTime = 0.0f;
float FPS = 0.0f;

static int playerID;

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

void OnEscapeKey(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

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

static void OnCursorMove(GLFWwindow* window, double xPos, double yPos)
{
	Application::Instance().SetMousePos(xPos, RESOLUTION_Y - yPos);

	if (Application::Instance().network != NULL)
	{
		playerID = 4201;
		//Application::Instance().network->sendEvent(playerID, xPos, RESOLUTION_Y - yPos);
	}
}

void OnLeftMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (Application::Instance().network != NULL)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		{
			Application::Instance().network->sendEvent(playerID, 1.0f, 0.0f);

			if (Application::Instance().GetGameState() == STATE_STARTGAME)
			{
				Application::Instance().OnMouseClickBox();
			}
		}
	}
}

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
	glfwSetKeyCallback(window, OnEscapeKey);
	// Return the position of the cursor position.
	glfwSetCursorPosCallback(window, OnCursorMove);
	// Check left mouse button.
	glfwSetMouseButtonCallback(window, OnLeftMouseButton);

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