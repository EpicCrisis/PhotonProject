
#pragma once

#include <GLFW/glfw3.h>
#include "UVRender.h"
#include "lodepng.h"
#include "Vector2.h"

class Renderer
{
public:
	static void LoadPNG(const char* path, GLuint textureID, unsigned int& width, unsigned int& height);
	static void LoadTexture(const char* path, GLuint textureID, unsigned int& width, unsigned int& height);
	static void RenderGeometry(GLuint textureID, GLfloat* vertices, GLfloat* texCoords, GLubyte* colors);
				
	static void RenderSquare(GLuint textureID, int x, int y, int width, int height, int depth, GLubyte r, GLubyte g, GLubyte b, GLubyte a, Vector2 minUV, Vector2 maxUV);
	static void RenderSquare(GLuint textureID, int x, int y, int width, int height, int depth, GLubyte r, GLubyte g, GLubyte b, GLubyte a);
	static void RenderSquare(GLuint textureID, int x, int y, int width, int height, int depth);
};