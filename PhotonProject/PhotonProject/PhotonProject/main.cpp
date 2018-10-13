
#include <iostream>
#include "MyPhoton.h"
#include <Windows.h>
#include <gl/GLU.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include <ctime>

const int RESOLUTION_X = 800;
const int RESOLUTION_Y = 600;

const int TEXTURE_COUNT = 2;

// Texture function.
enum Texture
{
	T_NOMAD = 0,
};
GLuint mTextureID[TEXTURE_COUNT];
unsigned int mTextureSize[TEXTURE_COUNT][2];

// Photon function.
MyPhoton* network = NULL;
const int playerID = 0;
float cursorPos[2];

// Application function.
bool bVSync = true;
float deltaTime;
float lastUpdateTime;
float FPS;

void OnWindowResized(GLFWwindow* window, int width, int height);
void OnCursorMove(GLFWwindow* window, double xPos, double yPos);
void OnExitKey(GLFWwindow* window, int key, int scanCode, int action, int mods);
void OnLeftMouseButton(GLFWwindow* window, int button, int action, int mods);

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

void OnCursorMove(GLFWwindow* window, double xPos, double yPos)
{
	if (network != NULL)
	{
		int myID = 4201;
		network->sendEvent(myID, xPos, yPos - RESOLUTION_Y);
	}
}

void OnExitKey(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	if (network != NULL)
	{
		if (action == GLFW_PRESS)
		{
			if (key == GLFW_KEY_ESCAPE)
			{
				glfwSetWindowShouldClose(window, GL_TRUE);
			}
		}
	}
}

void OnLeftMouseButton(GLFWwindow * window, int button, int action, int mods)
{
	if (network != NULL)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		{
			network->sendEvent(playerID, 1.0f, 0.0f);
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
	// Check for escape (exit) key.
	glfwSetKeyCallback(window, OnExitKey);
	// Return the position of the cursor position.
	glfwSetCursorPosCallback(window, OnCursorMove);
	// Check for left mouse button.
	glfwSetMouseButtonCallback(window, OnLeftMouseButton);

	// Support alpha channel.
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);

	// Load Textures.
	// Need to call after window's created.
	glEnable(GL_TEXTURE_2D);
	glGenTextures(TEXTURE_COUNT, mTextureID);

	Renderer::LoadTexture("NomadAvatar.png", mTextureID[T_NOMAD], mTextureSize[T_NOMAD][0], mTextureSize[T_NOMAD][1]);

	// Initialize network.
	network = new MyPhoton();
	network->connect();

	while (!glfwWindowShouldClose(window))
	{
		// Render here,
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Calculate delta time and FPS.
		deltaTime = (float)glfwGetTime() - lastUpdateTime;
		lastUpdateTime = (float)glfwGetTime();
		FPS = 1.0f / deltaTime;

		Renderer::RenderSquare
		(mTextureID[T_NOMAD], (int)cursorPos[0], (int)cursorPos[1] - RESOLUTION_Y, 380, 370, 0);

		Renderer::RenderSquare
		(mTextureID[T_NOMAD], (int)network->cursorPos[0], (int)network->cursorPos[1] - RESOLUTION_Y, 380, 370, 0);

		network->run();
	
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}