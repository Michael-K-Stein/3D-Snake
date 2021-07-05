#pragma once

struct _Window {
	GLFWwindow * Window;
	int Width;
	int Height;
} Window;

struct _AxisVectors {
	vec3 X;
	vec3 Y;
	vec3 Z;
	vec4 Centre;
} WorldAxis = {
	{1.f,0.f,0.f}, { 0.f,1.f,0.f }, { 0.f,0.f,1.f },
	{ 0.f,0.f,0.f, 0.f }
};

struct _WorldMatricies {
	mat4 view;
	mat4 proj;
} WorldMatricies = {
	{
		{1.f, 0.f, 0.f, 0.f},
		{0.f, 1.f, 0.f, 0.f},
		{0.f, 0.f, 1.f, 0.f},
		{0.f, 0.f, 0.f, 1.f} 
	},

	{
		{1.f, 0.f, 0.f, 0.f},
		{0.f, 1.f, 0.f, 0.f},
		{0.f, 0.f, 1.f, 0.f},
		{0.f, 0.f, 0.f, 1.f}
	}
};



struct _Shader {
	GLuint Program;

	GLuint Fragment;
	GLuint Vertex;

	GLuint positionAttrib;
	GLuint colorAttrib;

	GLuint uniTrans;
	GLuint uniView;
	GLuint uniProj;
	GLuint uniColor;
} Shader;