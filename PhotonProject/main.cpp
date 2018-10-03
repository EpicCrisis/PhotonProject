#include <iostream>
#include "MyPhoton.h"
#include <Windows.h>
#include <GL/GLU.h>
#include <GLFW/glfw3.h>

const int RESOLUTION_X = 800;
const int RESOLUTION_Y = 600;

MyPhoton* network = NULL;

void onWindowResized(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//! Use ortho2D view
	gluOrtho2D(0, width, 0, height);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

static void cursor_position_callback(GLFWwindow* window, double xPos, double yPos)
{
	if (network != NULL)
	{
		int myID = 4201;
		network->sendEvent(myID, xPos, yPos);
	}
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create m_a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(RESOLUTION_X, RESOLUTION_Y, "", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetWindowSizeCallback(window, onWindowResized);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	onWindowResized(window, RESOLUTION_X, RESOLUTION_Y);
	glfwSetCursorPosCallback(window, cursor_position_callback);

	network = new MyPhoton();
	network->connect();
	while (!glfwWindowShouldClose(window))
	{
		network->run();
	
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}