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



void DrawTriangle(point2 a, point2 b, point2 c) 
{
	float vertices[] = {
		a.x, a.y,
		b.x, b.y, 
		c.x, c.y
	};

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void DrawGasket(point2 a, point2 b, point2 c, int n)
{
	if (n > 0)
	{
		point2 ab = (a + b) / 2.0;
		point2 ca = (a + c) / 2.0;
		point2 bc = (b + c) / 2.0;

		DrawGasket(a, ab, ca, n - 1);
		DrawGasket(c, bc, ca, n - 1);
		DrawGasket(b, bc, ab, n - 1);
	}
	else
	{
		DrawTriangle(a, b, c);
	}

}


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
	
	



	Shader shader("res/shader/vertexShader.shader", "res/shader/fragmentShader.shader");
	shader.use();

	

	point2 a = { -0.5f, -0.5f };
	point2 b = {  0.0f,  0.5f };
	point2 c = {  0.5f, -0.5f };

	glClearColor(0.2f, 0.2f, 0.3f, 1.0f);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		DrawGasket(a, b, c, 10);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	
}

