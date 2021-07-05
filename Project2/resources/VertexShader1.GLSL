#version 150 core

in vec3 position;

out vec3 Color;

uniform mat4 trans;
uniform mat4 view;
uniform mat4 proj;
uniform vec3 color;

void main()
{
	Color = color;
	gl_Position = proj * view * trans * vec4(position, 1.0);
}