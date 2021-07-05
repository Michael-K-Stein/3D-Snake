#pragma once

#include "../OpenGL_Headers.h"

enum SNAKE_DIR {
	POSITIVE_X,
	NEGATIVE_X,
	POSITIVE_Y,
	NEGATIVE_Y
};
typedef enum SNAKE_DIR SNAKE_DIR;

struct _Snake {
	int Body[64 * 6];
	int Length;
	SNAKE_DIR Direction;

	BOARD_PLANES Plane;
	int x, y;
};
typedef struct _Snake Snake;

Snake * Snake_Init() {

	Snake * s = (Snake*)calloc(1, sizeof(Snake));

	memset(s->Body, -1, 64 * 6 * sizeof(int));

	s->Length = 4;
	s->Direction = POSITIVE_X;

	s->Plane = FRONT_PLANE;
	s->x = 0;
	s->y = 0;

	s->Body[0] = 0;

	return s;
}

int Snake_MovePositiveX(Snake * s) {
	if (s->x == 7) {
		if (s->Plane < 4 && s->Plane >= 0) {
			s->Plane = (s->Plane + 1) % 4;
			s->x = 0;
		}
		else if (s->Plane == BOTTOM_PLANE) {
			s->Plane = RIGHT_PLANE;
			s->x = s->y;
			s->y = 0; 
			s->Direction = POSITIVE_Y;
		}
		else if (s->Plane == TOP_PLANE) {
			s->Plane = RIGHT_PLANE;
			s->x = s->y;
			s->y = 7;
			s->Direction = NEGATIVE_Y;
		}
	}
	else {
		s->x++;
	}
	return s->x;
}
int Snake_MoveNegativeX(Snake * s) {
	if (s->x == 0) {
		if (s->Plane < 4 && s->Plane >= 0) {
			s->Plane = (s->Plane + 3) % 4;
			s->x = 7;
		}
		else if (s->Plane == BOTTOM_PLANE) {
			s->Plane = LEFT_PLANE;
			s->Direction = POSITIVE_Y;
			s->x = 7 - s->y;
			s->y = 0;
		}
		else if (s->Plane == TOP_PLANE) {
			s->Plane = LEFT_PLANE;
			s->x = 7 - s->y;
			s->y = 7;
			s->Direction = NEGATIVE_Y;
		}
	}
	else {
		s->x--;
	}
	return s->x;
}
int Snake_MovePositiveY(Snake * s) {
	if (s->y == 7) {
		if (s->Plane == BACK_PLANE) {
			s->Plane = TOP_PLANE;
			s->x = 7 - s->x;
			s->Direction = NEGATIVE_Y;
		} 
		else if (s->Plane == LEFT_PLANE) {
			s->Plane = TOP_PLANE;
			s->y = 7 - s->x;
			s->x = 0;
			s->Direction = POSITIVE_X;
		}
		else if (s->Plane == RIGHT_PLANE) {
			s->Plane = TOP_PLANE;
			s->y = s->x;
			s->x = 7;
			s->Direction = NEGATIVE_X;
		}
		else if (s->Plane < 4 && s->Plane >= 0) {
			s->Plane = TOP_PLANE;
			
			s->y = 0;
		}
		else if (s->Plane == TOP_PLANE) {
			s->Plane = BACK_PLANE;
			s->x = 7 - s->x;
			s->Direction = NEGATIVE_Y;
		}
		else if (s->Plane == BOTTOM_PLANE) {
			s->Plane = BACK_PLANE;
			s->y = 0;
			s->x = 7 - s->x;
		}
	}
	else {
		s->y++;
	}
	return s->y;
}
int Snake_MoveNegativeY(Snake * s) {
	if (s->y == 0) {
		if (s->Plane == LEFT_PLANE) {
			s->Plane = BOTTOM_PLANE;
			s->y = 7 - s->x;
			s->x = 0;
			s->Direction = POSITIVE_X;
		}
		else if (s->Plane == RIGHT_PLANE) {
			s->Plane = BOTTOM_PLANE;
			s->y = s->x;
			s->x = 7;
			s->Direction = NEGATIVE_X;
		}
		else if (s->Plane < 4 && s->Plane >= 1) {
			s->Plane = BOTTOM_PLANE;
			s->y = 7;
			s->x = 7 - s->x;
		}
		else if (s->Plane == FRONT_PLANE) {
			s->Plane = BOTTOM_PLANE;
			s->Direction = POSITIVE_Y;
		}
		else if (s->Plane == TOP_PLANE) {
			s->Plane = FRONT_PLANE;
			s->y = 7;
			s->Direction = NEGATIVE_Y;
		}
		else if (s->Plane == BOTTOM_PLANE) {
			s->Plane = FRONT_PLANE;
			//s->x = 7 - s->x;
			s->Direction = POSITIVE_Y;
		}
	}
	else {
		s->y--;
	}
	return s->y;
}

int Snake_Update(Snake * s) {

	// Update Head
	switch (s->Direction) {
	case POSITIVE_X:
		Snake_MovePositiveX(s);
		break;
	case NEGATIVE_X:
		Snake_MoveNegativeX(s);
		break;
	case POSITIVE_Y:
		Snake_MovePositiveY(s);
		break;case NEGATIVE_Y:
			Snake_MoveNegativeY(s);
		break;
	}

	// Update Body
	for (int i = s->Length; i >= 1; i--) {
		s->Body[i] = s->Body[i - 1];
	}

	s->Body[0] = (s->Plane * 64) + (s->y * 8) + s->x;

	return 0;
}