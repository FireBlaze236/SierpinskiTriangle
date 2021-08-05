#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

#define POINT_COUNT 5000

struct point2 {
	float x;
	float y;
	point2() { x = y = 0.0f; }

	point2(float a, float b)
	{
		x = a;
		y = b;
	}

	point2 operator +(point2& other)
	{
		return point2(x + other.x, y + other.y);
	}

	point2 operator /(float factor)
	{
		return point2(x / factor, y / factor);
	}
	
};

int main()
{
	if (!glfwInit())
	{
		std::cout << "GLFW intialization failed" << std::endl;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(640, 480, "Sierpinski", NULL, NULL);

	if (!window)
	{
		std::cout << "GLFW Window creation failed" << std::endl;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();


	//Triangle
	/*float vertices[] = {
		0.0f, 0.5f, 1.0f,
	   -0.5f, -0.5f, 1.0f,
		0.5f, -0.5f, 1.0f
	};*/

	point2 vertices[3] = { point2(-0.5f, -0.5f), point2(0.5f, -0.5f), point2(0.0f, 0.5f) };
	point2 points[POINT_COUNT];

	points[0] = point2(0.2f, 0.1f);
	
	int idx = 0;
	float arr[POINT_COUNT * 2] = { 0 };

	for (int i = 1; i < POINT_COUNT; i++)
	{
		int j = rand() % 3;

		points[i] = (points[i - 1] + vertices[j]) / 2.0f;

		arr[idx] = points[i].x;
		arr[idx + 1] = points[i].y;

		idx += 2;
	}

	



	Shader shader("res/shader/vertexShader.shader", "res/shader/fragmentShader.shader");

	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	shader.use();

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(arr), arr , GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
	glEnableVertexAttribArray(0);


	

	glClearColor(0.2f, 0.2f, 0.3f, 1.0f);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);

		glDrawArrays(GL_POINTS, 0, POINT_COUNT);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	
}
