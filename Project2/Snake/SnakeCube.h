#pragma once

#include "../Objects/Cube.h"

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
	RED
};
typedef enum BOARD_COLOR BOARD_COLOR;

struct _BOARD_ACTUAL_COLORS {
	float Array[4 * 3];
} BOARD_ACTUAL_COLOR = {
	0.f, 0.f, 0.f,
	0.6627f, 0.6627f, 0.6627f,
	0.f, 1.f, 0.f,
	1.f, 0.f, 0.f
};

struct _BOARD_PLANES_OFFSET {
	vec3 offsets[6];
} BOARD_PLANES_OFFSET = {
	0.f, 0.f, 0.f,
	7.f, 0.f, 0.f,
	7.f, 0.f, 7.f,
	0.f, 0.f, 7.f,
	0.f, 0.f, 0.f,
	0.f, 7.f, 0.f
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


struct _SnakeCube {

	BOARD_COLOR side_colors[6];


	BOARD_PLANES Plane;
	int x, y; // Relative to the plane (0,0 - top left).

	Cube * cube;

};
typedef struct _SnakeCube SnakeCube;


SnakeCube * SnakeCube_New(BOARD_PLANES plane, int x, int y);
SnakeCube ** GenerateSnakeCubes();
int SnakeCube_Draw(SnakeCube * sc);
int SnakeCube_RecolorBase(SnakeCube * sc);

// IMPLEMENTATION

int SnakeCube_RecolorBase(SnakeCube * sc) {
	for (int i = 0; i < 6; i++) {
		memcpy(sc->cube->colors + (i * 3), BOARD_ACTUAL_COLOR.Array + (sc->side_colors[i] * 3), 3 * sizeof(float));
	}
	return 0;
}
SnakeCube * SnakeCube_New(BOARD_PLANES plane, int x, int y) {

	SnakeCube * sc = (SnakeCube*)calloc(1, sizeof(SnakeCube));

	sc->Plane = plane;
	sc->x = x;
	sc->y = y;

	for (int i = 0; i < 6; i++) {
		sc->side_colors[i] = GRAY;
	}

	sc->cube = Cube_New();

	glm_translate(sc->cube->model, BOARD_PLANES_OFFSET.offsets[plane]);

	vec3 scaledX, scaledY;

	glm_vec3_scale(BOARD_PLANE_RELATIVE_X.offsets[plane], x, scaledX);
	glm_vec3_scale(BOARD_PLANE_RELATIVE_Y.offsets[plane], y, scaledY);

	glm_translate(sc->cube->model, scaledX);
	glm_translate(sc->cube->model, scaledY);


	SnakeCube_RecolorBase(sc);


	return sc;

}
SnakeCube ** GenerateSnakeCubes() {

	SnakeCube ** board = (SnakeCube**)calloc(296, sizeof(SnakeCube*));

	for (int i = 0; i < 296; i++) {
		board[i] = SnakeCube_New();
	}

	printf("Generated %d snake cubes.\n", 296);

	return board;
}
int SnakeCube_Draw(SnakeCube * sc) {
	return Cube_Draw(sc->cube);
}