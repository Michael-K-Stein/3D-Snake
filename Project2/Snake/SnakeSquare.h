#pragma once

#include <cglm/cglm.h>
#include "../OpenGL_Headers.h"
#include "../WorldStructs.h"

float square_vertices[] = {
	 -0.5f,  -0.5f, -0.5f,		0.5f, -0.5f, -0.5f,	// Top Left		Front
	 0.5f,  -0.5f, -0.5f,		0.5f, -0.5f, -0.5f,	// Top Right	Front
	 0.5f,  0.5f, -0.5f,		0.5f, -0.5f, -0.5f,	// Bottom Right Front
	 -0.5f,  0.5f, -0.5f,		0.5f, -0.5f, -0.5f,	// Bottom Left	Front
};

enum BOARD_PLANES {
	FRONT_PLANE,
	RIGHT_PLANE,
	BACK_PLANE,
	LEFT_PLANE,
	TOP_PLANE,
	BOTTOM_PLANE
};
typedef enum BOARD_PLANES BOARD_PLANES;



enum BOARD_COLOR {
	BLACK,
	GRAY,
	GREEN,
	RED,

	A,
	B,
	C,
	D,
	E,
	F
};
typedef enum BOARD_COLOR BOARD_COLOR;

struct _BOARD_ACTUAL_COLORS {
	float Array[10 * 3];
} BOARD_ACTUAL_COLOR = {
	0.f, 0.f, 0.f,
	0.6627f, 0.6627f, 0.6627f,
	0.f, 1.f, 0.f,
	1.f, 0.f, 0.f,

	1.f, 0.f, 0.f,
	0.f, .5f, 0.f,
	0.f, 0.f, 1.f,
	1.f, 1.f, 0.f,
	0.f, 1.f, 1.f,
	1.f, 0.f, 1.f
};

struct _BOARD_PLANES_OFFSET {
	vec3 offsets[6];
} BOARD_PLANES_OFFSET = {
	-3.5f, -3.5f, -3.5f,
	3.5f, -3.5f, -3.5f,
	3.5f, -3.5f, 3.5f,
	-3.5f, -3.5f, 3.5f,
	-3.5f, 3.5f, -3.5f,
	-3.5f, -3.5f, -3.5f
};

struct _BOARD_PLANE_RELATIVE_X {
	vec3 offsets[6];
} BOARD_PLANE_RELATIVE_X = {
	1.f, 0.f, 0.f,
	0.f, 0.f, 1.f,
	-1.f, 0.f, 0.f,
	0.f, 0.f, -1.f,
	1.f, 0.f, 0.f,
	1.f, 0.f, 0.f,
};

struct _BOARD_PLANE_RELATIVE_Y {
	vec3 offsets[6];
} BOARD_PLANE_RELATIVE_Y = {
	0.f, 1.f, 0.f,
	0.f, 1.f, 0.f,
	0.f, 1.f, 0.f,
	0.f, 1.f, 0.f,
	0.f, 0.f, 1.f,
	0.f, 0.f, 1.f,
};


struct _SnakeSquare {

	BOARD_COLOR color;
	float actual_color[3];

	BOARD_PLANES Plane;
	int x, y; // Relative to the plane (0,0 - top left).

	mat4 model;
};
typedef struct _SnakeSquare SnakeSquare;



// Declerations

SnakeSquare * SnakeSquare_New(BOARD_PLANES plane, int x, int y);
SnakeSquare ** GenerateBoard();
int SnakeSquare_Draw(SnakeSquare * ss);
int SnakeSquare_Recolor(SnakeSquare * ss);

// Implementations

SnakeSquare * SnakeSquare_New(BOARD_PLANES plane, int x, int y) {

	SnakeSquare * ss = (SnakeSquare*)calloc(1, sizeof(SnakeSquare));

	ss->Plane = plane;
	ss->x = x;
	ss->y = y;

	ss->color = GRAY;

	mat4 m = {
			{1.f, 0.f, 0.f, 0.f},
			{0.f, 1.f, 0.f, 0.f},
			{0.f, 0.f, 1.f, 0.f},
			{0.f, 0.f, 0.f, 1.f} };

	glm_translate(m, BOARD_PLANES_OFFSET.offsets[plane]);

	vec3 scaledX, scaledY;

	//if (plane == TOP_PLANE || plane == BOTTOM_PLANE) { int t = x; x = y; y = t; }

	glm_vec3_scale(BOARD_PLANE_RELATIVE_X.offsets[plane], x, scaledX);
	glm_vec3_scale(BOARD_PLANE_RELATIVE_Y.offsets[plane], y, scaledY);

	glm_translate(m, scaledX);
	glm_translate(m, scaledY);

	memcpy(ss->model, m, sizeof(m));

	switch (ss->Plane){
	case FRONT_PLANE:
		break;
	case RIGHT_PLANE:
		glm_rotate(ss->model, glm_rad(-90.f), WorldAxis.Y);
		break;
	case LEFT_PLANE:
		glm_rotate(ss->model, glm_rad(90.f), WorldAxis.Y);
		break;
	case BACK_PLANE:
		glm_rotate(ss->model, glm_rad(180.f), WorldAxis.Y);
		break;
	case TOP_PLANE:
		glm_rotate(ss->model, glm_rad(90.f), WorldAxis.X);
		break;
	case BOTTOM_PLANE:
		glm_rotate(ss->model, glm_rad(-90.f), WorldAxis.X);
		break;
	}

	SnakeSquare_Recolor(ss);


	return ss;
}

SnakeSquare ** GenerateBoard() {
	SnakeSquare ** board = (SnakeSquare**)calloc(8 * 8 * 6, sizeof(SnakeSquare*));

	for (int p = 0; p < 6; p++) {

		for (int y = 0; y < 8; y++) {
			for (int x = 0; x < 8; x++) {

				board[(p * 64) + (y * 8) + x] = SnakeSquare_New((BOARD_PLANES)p, x, y);

			}
		}

	}

	return board;
}

int SnakeSquare_Draw(SnakeSquare * ss) {

	/*// Black Square
	mat4 tmp_model;
	memcpy(tmp_model, ss->model, sizeof(mat4));

	//glm_translate(tmp_model, towards_centre3);

	glm_mat4_scale(tmp_model, 0.1);

	glUniformMatrix4fv(Shader.uniTrans, 1, GL_FALSE, (GLfloat*)tmp_model);
	

	glUniform3f(Shader.uniColor, BOARD_ACTUAL_COLOR.Array[0], BOARD_ACTUAL_COLOR.Array[1], BOARD_ACTUAL_COLOR.Array[2]);
	glBegin(GL_QUADS);
	for (int k = 0; k < 4; k++) {
		glVertex3f(square_vertices[(k * 6) + 0], square_vertices[(k * 6) + 1], square_vertices[(k * 6) + 2]);
	}
	glEnd();*/


	// Colored Square
	float inner_scale = 0.9f;

	glUniformMatrix4fv(Shader.uniTrans, 1, GL_FALSE, (GLfloat*)ss->model);

	glUniform3f(Shader.uniColor, ss->actual_color[0], ss->actual_color[1], ss->actual_color[2]);
	glBegin(GL_QUADS);
	for (int k = 0; k < 4; k++) {
		glVertex3f(square_vertices[(k * 6) + 0] * inner_scale, square_vertices[(k * 6) + 1] * inner_scale, square_vertices[(k * 6) + 2] * inner_scale);
	}
	glEnd();

	return 0;
}

int SnakeSquare_Recolor(SnakeSquare * ss) {
	memcpy(ss->actual_color, BOARD_ACTUAL_COLOR.Array + (ss->color * 3), 3 * sizeof(float));
	return 0;
}