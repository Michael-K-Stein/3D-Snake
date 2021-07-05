#pragma once

#include <Windows.h>

// Must be before GLFW
#define GLEW_STATIC
#pragma comment(lib, "glew32s")
#include <GL/glew.h>

#pragma comment(lib, "glfw3")
#include <GLFW\glfw3.h>

#include <cglm/cglm.h>

#define nullptr NULL