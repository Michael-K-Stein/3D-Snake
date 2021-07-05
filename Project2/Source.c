
#include "OpenGL_Headers.h"
#include "Objects/Shaders.h"

#include "Window.h"

#include "WorldStructs.h"
#include "Camera.h"

#include "Objects/Cube.h"
#include "Snake/SnakeSquare.h"
//#include "Snake/SnakeCube.h"

#include "Snake/SnakeGeneral.h"

#define CGLM_ALL_UNALIGNED 

int main(int argc, char* argv[])
{
	glfwInit();

	GenerateWindow();

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	// Create Vertex Array Object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create a Vertex Buffer Object and copy the vertex data to it
	GLuint vbo;
	glGenBuffers(1, &vbo);

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

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Create an element array
	GLuint ebo;
	glGenBuffers(1, &ebo);

	GLuint elements[] = {
		0, 1, 2, 3,
		4, 5, 6, 7,
		8, 9, 10, 11,
		12, 13, 14, 15,
		16, 17, 18, 19,
		20, 21, 22, 23
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	LoadShaders();

	

	glEnable(GL_DEPTH_TEST);

	mat4 model = {
			{1.f, 0.f, 0.f, 0.f},
			{0.f, 1.f, 0.f, 0.f},
			{0.f, 0.f, 1.f, 0.f},
			{0.f, 0.f, 0.f, 1.f} };



	SnakeSquare ** board = GenerateBoard();

	board[0]->color = GREEN;

	SnakeSquare_Recolor(board[0]);

	/*Cube * cubes[64];
	for (int i = 0; i < 64; i++) {
		cubes[i] = Cube_New();
		glm_translate_x(cubes[i]->model, (1.f * (i%8)) - 4.f);
		glm_translate_y(cubes[i]->model, (1.f * (i/8)) - 4.f);
	}*/

	
	//Camera_Move_Z(5);
	Camera_Rotate_Y(0);

	UpdateView();
	UpdateProjection(Window.Width, Window.Height);

	Snake * snake = Snake_Init();
	Cube ** cubes = (Cube**)calloc(16, sizeof(Cube*));
	for (int i = 0; i < 16; i++) {
		cubes[i] = Cube_New();
	}
	for (int i = 0; i < 6; i++) {
		memcpy(cubes[0]->colors + (i * 3), BOARD_ACTUAL_COLOR.Array + (B * 3), 3 * sizeof(float));
	}


	int fruit = rand() % (8*8*6);

	double last_time = glfwGetTime();
	double timeout = 0.3;

	double cam_update_factor = 20.0;
	double last_cam_update = glfwGetTime();
	double cam_timeout = timeout / cam_update_factor;

	while (!glfwWindowShouldClose(Window.Window))
	{
		if (glfwGetKey(Window.Window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(Window.Window, GL_TRUE);
		}
		if (glfwGetKey(Window.Window, GLFW_KEY_LEFT) == GLFW_PRESS) {
			if (snake->Plane == BOTTOM_PLANE) {
				snake->Direction = POSITIVE_Y;
			}
			else {
				snake->Direction = POSITIVE_X;
			}
		}
		if (glfwGetKey(Window.Window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
			if (snake->Plane == BOTTOM_PLANE) {
				snake->Direction = NEGATIVE_Y;
			}
			else {
				snake->Direction = NEGATIVE_X;
			}
		}
		if (glfwGetKey(Window.Window, GLFW_KEY_UP) == GLFW_PRESS) {
			snake->Direction = POSITIVE_Y;
		}
		if (glfwGetKey(Window.Window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			if (snake->Plane == TOP_PLANE) {
				snake->Direction = NEGATIVE_X;
			}
			else {
				snake->Direction = NEGATIVE_Y;
			}
		}


		// Swap buffers
		glfwSwapBuffers(Window.Window);
		glfwPollEvents();


		// Clear the screen to black
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (last_time + timeout <= glfwGetTime()) {
			Snake_Update(snake);
			if (snake->Body[0] == fruit) {
				snake->Length++;
				fruit = rand() % (8 * 8 * 6);
			}
			last_time = glfwGetTime();
		}

		for (int p = 0; p < 6; p++) {
			for (int i = 0; i < 8 * 8; i++) {
				board[(p * 64) + i]->color = GRAY; //A + p;
			}
		}


		for (int i = 0; i < snake->Length; i++) {
			if (snake->Body[i] != -1) {
				board[snake->Body[i]]->color = GREEN;
			}
		}

		board[fruit]->color = RED;

		board[snake->Body[0]]->color = B;

		float angle_x = ((snake->x / 8.f) * 90.f);
		if (snake->Plane < 4) {
			angle_x += snake->Plane * 90.f;
		}

		angle_x = -glm_rad(angle_x + 180.f - 45.f);

		float angle_y = (( ((snake->Plane == BOTTOM_PLANE) ? (7-snake->y) : snake->y) / 8.f) * (90.f));
		if (snake->Plane == TOP_PLANE) { angle_y += 90.f; }
		else if (snake->Plane == BOTTOM_PLANE) { angle_y += 270.f; }

		angle_y = glm_rad(angle_y - 45.f);

		/*vec3 tmp = { 0.0f, 0.0f, -1.f };
		glm_vec3_rotate(tmp, angle_x, WorldAxis.Y);
		//glm_vec3_rotate(tmp, angle_y, WorldAxis.Z);
		memcpy(Camera.Front, tmp, 3 * sizeof(float));
		Camera.Front[1] = sinf(angle_y);
		Camera.Front[0] *= cosf(angle_y);
		*/

		vec4 ones = { 0.f, 0.f, 0.f, 1.f };
		mat4 tmp_mat; memcpy(tmp_mat, board[snake->Body[0]]->model, sizeof(mat4));
		glm_mat4_mulv(tmp_mat, ones, ones);
		glm_vec4_scale(ones, 2, Camera.TargetPosition);

		if (last_cam_update + cam_timeout <= glfwGetTime()) {

			vec4 cam_move_tmp = { 0.f, 0.f ,0.f , 0.f };

			glm_vec4_sub(Camera.TargetPosition, Camera.Position, cam_move_tmp);

			glm_vec4_scale(cam_move_tmp, 1.0 / cam_update_factor, cam_move_tmp);

			glm_vec4_add(Camera.Position, cam_move_tmp, Camera.Position);

			last_cam_update = glfwGetTime();

		}

		/*Camera.Position[0] = Camera.radius * sinf(angle_x) * sinf(-angle_y);
		Camera.Position[1] = Camera.radius * sinf(angle_y);
		Camera.Position[2] = Camera.radius * cosf(angle_x) * cosf(angle_y);*/

		/*if (snake->Plane == TOP_PLANE) {
			Camera.Position[0] = 0.f;// Camera.radius * sinf(angle_x);
			Camera.Position[1] = -Camera.radius; //* sinf(angle_y);
			Camera.Position[2] = 0.f;// Camera.radius * cosf(angle_x);
		}*/

		vec4 camera_dir_tmp;
		
		glm_vec4_sub(WorldAxis.Centre, Camera.Position, camera_dir_tmp);
		glm_normalize(camera_dir_tmp);

		memcpy(Camera.Front, camera_dir_tmp, 3 * sizeof(float));

		UpdateView();

		glUniformMatrix4fv(Shader.uniView, 1, GL_FALSE, WorldMatricies.view);


		glUniformMatrix4fv(Shader.uniProj, 1, GL_FALSE, WorldMatricies.proj);

		for (int i = 0; i < 8 * 8 * 6; i++) {
			/*if (snake->Body[i] != -1) {
				SnakeSquare_Recolor(board[snake->Body[i]]);
			}*/
			SnakeSquare_Recolor(board[i]);
			SnakeSquare_Draw(board[i]);
		}

		for (int i = 0; i < snake->Length; i++) {
			if (snake->Body[i] != -1) {
				//memcpy(cubes[i]->model, board[snake->Body[i]]->model, sizeof(mat4));
				Cube_Remodel(cubes[i], board[snake->Body[i]]->model, board[snake->Body[i]]->Plane);
				Cube_Draw(cubes[i]);
			}
		}

	}

	DeleteShaders();

	glDeleteBuffers(1, &ebo);
	glDeleteBuffers(1, &vbo);

	glDeleteVertexArrays(1, &vao);
}