#pragma once

#include "../OpenGL_Headers.h"

struct _Point2D {
	float x;
	float y;
};
typedef struct _Point2D Point2D;

typedef Point2D TriangleVerticies2D[3];

struct _Triangle2D {
	TriangleVerticies2D verticies;
};
typedef struct _Triangle2D Triangle2D;

Triangle2D * CreateObject_Triangle2D() {

	Triangle2D * triangle = (Triangle2D*)malloc(sizeof(Triangle2D));

	// Vertext Buffer Object
	GLuint vbo;
	// "malloc" a buffer in the GPU (implemented by OpenGL)
	glGenBuffers(1, &vbo);
	// Set 'vbo' to the activate buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Copy the verticies into the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(TriangleVerticies2D), triangle->verticies, GL_STATIC_DRAW);

	

	return triangle;
}