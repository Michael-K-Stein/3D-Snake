#pragma once

#include <cglm/cglm.h>
#include "../OpenGL_Headers.h"
#include "../WorldStructs.h"
#include "../Snake/SnakeSquare.h"

float vertices[] = {
	 -0.5f,  -0.5f, -0.5f,		0.5f, -0.5f, -0.5f,	// Top Left		Front
	 0.5f,  -0.5f, -0.5f,		0.5f, -0.5f, -0.5f,	// Top Right	Front
	 0.5f,  0.5f, -0.5f,		0.5f, -0.5f, -0.5f,	// Bottom Right Front
	 -0.5f,  0.5f, -0.5f,		0.5f, -0.5f, -0.5f,	// Bottom Left	Front

	 -0.5f,  -0.5f, 0.5f,		-0.5f, 0.5f, -0.5f,	// Top Left		Back
	 0.5f,  -0.5f, 0.5f,		-0.5f, 0.5f, -0.5f,	// Top Right	Back
	 0.5f,  0.5f, 0.5f,			-0.5f, 0.5f, -0.5f,	// Bottom Right Back
	 -0.5f,  0.5f, 0.5f,		-0.5f, 0.5f, -0.5f,	// Bottom Left	Back

	 -0.5f,  -0.5f, -0.5f,		-0.5f, -0.5f, 0.5f,	// Top Left		Left
	 -0.5f,  -0.5f, 0.5f,		-0.5f, -0.5f, 0.5f,	// Top Right	Left
	 -0.5f,  0.5f, 0.5f,		-0.5f, -0.5f, 0.5f,	// Bottom Right Left
	 -0.5f,  0.5f, -0.5f,		-0.5f, -0.5f, 0.5f,	// Bottom Left	Left

	 0.5f,  -0.5f, -0.5f,		0.5f, 0.5f, -0.5f,	// Top Left		Right
	 0.5f,  -0.5f, 0.5f,		0.5f, 0.5f, -0.5f,	// Top Right	Right
	 0.5f,  0.5f, 0.5f,			0.5f, 0.5f, -0.5f,	// Bottom Right Right
	 0.5f,  0.5f, -0.5f,		0.5f, 0.5f, -0.5f,	// Bottom Left	Right

	 -0.5f,  -0.5f, -0.5f,		-0.5f, 0.5f, 0.5f,	// Top Left		Top
	 -0.5f,  -0.5f, 0.5f,		-0.5f, 0.5f, 0.5f,	// Top Right	Top
	 0.5f,  -0.5f, 0.5f,		-0.5f, 0.5f, 0.5f,	// Bottom Right Top
	 0.5f,  -0.5f, -0.5f,		-0.5f, 0.5f, 0.5f,	// Bottom Left	Top

	 -0.5f,  0.5f, -0.5f,		0.5f, -0.5f, 0.5f,	// Top Left		Bottom
	 -0.5f,  0.5f, 0.5f,		0.5f, -0.5f, 0.5f,	// Top Right	Bottom
	 0.5f,  0.5f, 0.5f,			0.5f, -0.5f, 0.5f,	// Bottom Right Bottom
	 0.5f,  0.5f, -0.5f,		0.5f, -0.5f, 0.5f,	// Bottom Left	Bottom
};


struct _Cube {
	mat4 model;
	float colors[3 * 6];
};
typedef struct _Cube Cube;

GLuint vao, vbo, ebo;

Cube * Cube_New();
int Cube_Draw(Cube * self);
int Cube_Init();
int Cube_Terminate();
int Cube_Remodel(Cube * self, mat4 base_model, BOARD_PLANES plane);

// IMPLEMENTATION

Cube * Cube_New() {
	Cube * c = (Cube*)calloc(1, sizeof(Cube));
	mat4 m = {
			{1.f, 0.f, 0.f, 0.f},
			{0.f, 1.f, 0.f, 0.f},
			{0.f, 0.f, 1.f, 0.f},
			{0.f, 0.f, 0.f, 1.f} };

	memcpy(c->model, m, sizeof(m));

	for (int i = 0; i < 6; i++) {
		memcpy(c->colors + (i * 3), BOARD_ACTUAL_COLOR.Array+(GREEN*3), 3 * sizeof(float));
	}

	return c;
}

int Cube_Draw(Cube * self) {
	glUniformMatrix4fv(Shader.uniTrans, 1, GL_FALSE, (GLfloat*)self->model);

	// Draw a rectangle from the 6 QUADS using 24 indices
	
	float scale = 1.f;

	for (int i = 0; i < 6; i++) {
		//glColor3f(self->colors[(i*3) +0], self->colors[(i * 3) + 1], self->colors[(i * 3) + 2]);
		glUniform3f(Shader.uniColor, self->colors[(i * 3) + 0], self->colors[(i * 3) + 1], self->colors[(i * 3) + 2]);
		glBegin(GL_QUADS);
		for (int k = 0; k < 4; k++) {
			glVertex3f(vertices[(i * 24) + (k * 6) + 0] * scale, vertices[(i * 24) + (k * 6) + 1] * scale, vertices[(i * 24) + (k * 6) + 2] * scale);
		}
		glEnd();
	}

	//glDrawElements(GL_QUADS, 4 * 6, GL_UNSIGNED_INT, 0);

	return 0;
}

int Cube_Init() {

	// Create Vertex Array Object
	//GLuint vao;

}

int Cube_Terminate() {
	glDeleteBuffers(1, &ebo);
	glDeleteBuffers(1, &vbo);

	glDeleteVertexArrays(1, &vao);
}

int Cube_Remodel(Cube * self, mat4 base_model, BOARD_PLANES plane) {
	memcpy(self->model, base_model, sizeof(mat4));

	//glm_mat4_scale(self->model, 0.5f);

	/*vec4 offset_X = { 1.f ,0.f ,0.f, 1.f };
	vec4 offset_Y = { 0.f ,1.f ,0.f, 1.f };
	vec4 offset_Z = { 0.f ,0.f ,1.f, 1.f };
	


	glm_mat4_mulv(base_model, offset_X, offset_X);
	glm_mat4_mulv(base_model, offset_Y, offset_Y);
	glm_mat4_mulv(base_model, offset_Z, offset_Z);

	

	glm_vec4_add(offset_X, offset_Y, trans);
	glm_vec4_add(offset_Z, trans, trans);

	glm_vec4_scale(trans, 0.05, trans);
	*/
	vec3 trans3; //memcpy(trans3, trans, 3 * sizeof(float));
	vec3 trans = { 0.f,0.f,0.f };

	switch (plane) {
	case FRONT_PLANE:
		glm_vec3_sub(trans, WorldAxis.Z, trans);
		break;
	case BACK_PLANE:
		glm_vec3_add(trans, WorldAxis.Z, trans);
		break;
	case LEFT_PLANE:
		glm_vec3_sub(trans, WorldAxis.X, trans);
		break;
	case RIGHT_PLANE:
		glm_vec3_add(trans, WorldAxis.X, trans);
		break;
	case TOP_PLANE:
		glm_vec3_add(trans, WorldAxis.Y, trans);
		break;
	case BOTTOM_PLANE:
		glm_vec3_sub(trans, WorldAxis.Y, trans);
		break;
	}

	glm_vec3_scale(trans, 1.1f, trans);

	//glm_vec4_copy3(trans, trans3);

	//glm_translate(self->model, trans);

	return 0;
}