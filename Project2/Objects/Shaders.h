#pragma once

#include <stdio.h>

#include "../OpenGL_Headers.h"
#include "../WorldStructs.h"

enum SHADER_TYPE {
	VERTEX_SHADER,
	FRAGMENT_SHADER
};
typedef enum SHADER_TYPE SHADER_TYPE;

int CompileShader(SHADER_TYPE type, char * file_name, GLuint * out) {

	FILE * f;
	if (fopen_s(&f, file_name, "r") != 0) {
		printf("Could not open '%s' shader file!\n", file_name);
		return -1;
	}

	fseek(f, 0, SEEK_END);

	int file_size = ftell(f);

	fseek(f, 0, SEEK_SET);

	char * file_buffer = (char*)calloc(file_size+1, 1);

	char ch;
	int i = 0;
	while ((ch = fgetc(f)) != EOF) {
		file_buffer[i++] = ch;
	}

	char * vertexSource = (char*)calloc(file_size+1, sizeof(char));

	strcpy_s(vertexSource, file_size+1, file_buffer);


	GLuint vertexShader = glCreateShader(type == VERTEX_SHADER ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);

	glCompileShader(vertexShader);

	GLint status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE) {
		free(file_buffer);
		free(vertexSource);
		fclose(f);
		printf("Failed to compile shader code!\n");
		printf("Error log: \n");

		char buffer[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, buffer);

		printf("%s\n", buffer);

		return -1;
	}

	*out = vertexShader;

	free(file_buffer);
	free(vertexSource);
	fclose(f);
	return 0;
}

int SpecifyShaderLayout() {
	// Specify the layout of the vertex data
	Shader.positionAttrib = glGetAttribLocation(Shader.Program, "position");
	glEnableVertexAttribArray(Shader.positionAttrib);
	glVertexAttribPointer(Shader.positionAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

	//Shader.colorAttrib = glGetAttribLocation(Shader.Program, "color");
	//glEnableVertexAttribArray(Shader.colorAttrib);
	//glVertexAttribPointer(Shader.colorAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));



	Shader.uniTrans = glGetUniformLocation(Shader.Program, "trans");
	Shader.uniView = glGetUniformLocation(Shader.Program, "view");
	Shader.uniProj = glGetUniformLocation(Shader.Program, "proj");
	Shader.uniColor = glGetUniformLocation(Shader.Program, "color");
}

int LoadShaders() {

	Shader.Program = glCreateProgram();

	int err = CompileShader(VERTEX_SHADER, "resources/VertexShader1.GLSL", &Shader.Vertex);
	err != CompileShader(FRAGMENT_SHADER, "resources/FragmentShader1.GLSL", &Shader.Fragment);

	if (err != 0) {
		return -1;
	}

	glAttachShader(Shader.Program, Shader.Vertex);
	glAttachShader(Shader.Program, Shader.Fragment);

	glBindFragDataLocation(Shader.Program, 0, "outColor");

	glLinkProgram(Shader.Program);
	glUseProgram(Shader.Program);


	SpecifyShaderLayout();

	return 0;
}

int DeleteShaders() {
	glDeleteProgram(Shader.Program);
	glDeleteShader(Shader.Fragment);
	glDeleteShader(Shader.Vertex);

	return 0;
}