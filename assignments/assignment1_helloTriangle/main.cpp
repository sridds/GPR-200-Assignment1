#include <stdio.h>
#include <math.h>

#include <ew/external/shader.h>
#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// this is the input vertex data for OpenGL. these are in normalized device coordinates
float vertices[] = {
	// positions          // colors
	-0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f, // BOTTOM RIGHT
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, // BOTTOM LEFT
	 0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f  // TOP
};

// for the quad (next assignment)
unsigned int indices[] = {
	0, 1, 3,  // first Triangle
	1, 2, 3   // second Triangle
};

int main() {
	printf("Initializing...");
	if (!glfwInit()) {
		printf("GLFW failed to init!");
		return 1;
	}
	// Create a window
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Triangle Solution", NULL, NULL);
	if (window == NULL) {
		printf("GLFW failed to create window");
		return 1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGL(glfwGetProcAddress)) {
		printf("GLAD Failed to load GL headers");
		return 1;
	}

	// build and compile shader program
	Shader ourShader("assets/vshader.vs", "assets/fshader.fs");

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO); // Bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).

	// Copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Set the vertex attributes pointers
	// -- Position attribute -- 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// -- Color attribute --
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	// glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	// Render loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		//Clear framebuffer
		glClearColor(0.3f, 0.4f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT); // clears the color buffer

		// update shader uniform
		double  timeValue = glfwGetTime();
		float colorValue = static_cast<float>(sin(timeValue) / 2.0 + 0.5);

		// Get the locations of the following variables
		ourShader.setFloat("value", colorValue);
		ourShader.setFloat("time", timeValue);

		// Render the triangle
		ourShader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//Drawing happens here!
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	printf("Shutting down...");
}
