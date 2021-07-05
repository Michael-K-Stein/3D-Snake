#pragma once

#include "OpenGL_Headers.h"
#include "WorldStructs.h"
#include "Camera.h"

int GenerateWindow();
void  window_size_callback(GLFWwindow* window, int width, int height);
void  window_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);



// IMPLEMENTATION

int GenerateWindow() {
	Window.Window = glfwCreateWindow(640, 480, "3D Snake - Michael K. Steinberg", NULL, NULL);
	glfwMakeContextCurrent(Window.Window);

	glfwGetWindowSize(Window.Window, &Window.Width, &Window.Height);
	glfwSetWindowSizeCallback(Window.Window, window_size_callback);
	glfwSetKeyCallback(Window.Window, window_key_callback);
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
	Window.Width = width;
	Window.Height = height;

	glViewport(0, 0, width, height);

	UpdateProjection(width, height);
}

float camera_move_factor = 0.2f;
void  window_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		switch (key) {
		case GLFW_KEY_W:
			Camera_Move_Y(camera_move_factor);
			break;
		case GLFW_KEY_A:
			Camera_Move_X(-camera_move_factor);
			break;
		case GLFW_KEY_S:
			Camera_Move_Y(-camera_move_factor);
			break;
		case GLFW_KEY_D:
			Camera_Move_X(camera_move_factor);
			break;
		case GLFW_KEY_Z:
			Camera_Rotate_Y(-0.05f);
			break;
		case GLFW_KEY_X:
			Camera_Rotate_Y(0.05f);
			break;
		}
	}
}