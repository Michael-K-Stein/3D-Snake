#pragma once

#include <cglm/cglm.h>

struct _Camera {
	vec4 Position;
	vec4 TargetPosition;
	vec4 Front;

	float angle;
	float radius;
} Camera = {
	{ 0.0f, 0.0f, 0.f, 0.f },
	{ 0.0f, 0.0f, 0.f, 0.f },
	{ 0.0f, 0.0f, -1.f, 0.f },

	0.f, 10.f
};

int UpdateView();
int UpdateProjection(int frameWidth, int frameHeight);

int Camera_Move_X(float s);
int Camera_Move_Y(float s);
int Camera_Move_Z(float s);

int Camera_Rotate_Y(float s);

// IMPLEMENTATION

int UpdateView() {
	vec3 tmp = { 0.0f, 0.0f, 0.f };
	glm_vec3_add(Camera.Position, Camera.Front, tmp);

	glm_lookat(Camera.Position, tmp, WorldAxis.Y, WorldMatricies.view);

	return 0;
}

int UpdateProjection(int frameWidth, int frameHeight) {
	float fov = 90.f;
	float nearPlane = 0.1f;
	float farPlane = 100.f;

	float framewidth = (float)frameWidth;
	float frameheight = (float)frameHeight;

	glm_perspective(glm_rad(fov), framewidth / frameheight, nearPlane, farPlane, WorldMatricies.proj);

	return 0;
}

int Camera_Move_X(float s) {
	vec3 tmp;

	glm_vec3_scale(WorldAxis.X, s, tmp);

	glm_vec3_add(Camera.Position, tmp, Camera.Position);

	return UpdateView();;
}
int Camera_Move_Y(float s) {
	vec3 tmp;

	glm_vec3_scale(WorldAxis.Y, s, tmp);

	glm_vec3_add(Camera.Position, tmp, Camera.Position);

	return UpdateView();;
}
int Camera_Move_Z(float s) {
	vec3 tmp;

	glm_vec3_scale(WorldAxis.Z, s, tmp);

	glm_vec3_add(Camera.Position, tmp, Camera.Position);

	return UpdateView();
}


int Camera_Rotate_Y(float s) {

	glm_vec3_rotate(Camera.Front, s, WorldAxis.Y);

	Camera.angle += s;

	Camera.Position[0] = Camera.radius * sinf(Camera.angle);
	Camera.Position[1] = 0.0f;
	Camera.Position[2] = Camera.radius * cosf(Camera.angle);

	return UpdateView();
}