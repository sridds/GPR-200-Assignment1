#include <stdio.h>
#include <math.h>

#include <ew/external/stb_image.h>
#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>

#include <sr/shader.h>
#include <sr/texture.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

float vertices[] = {
	// positions          // colors           // texture coords
	 0.4f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
	 0.4f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	-0.4f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	-0.4f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};

unsigned int indices[] = {  // note that we start from 0!
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
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Assignment 2", NULL, NULL);
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
	Shader ourShader("assets/h_vshader.vs", "assets/h_fshader.fs");
	Shader ourShader2("assets/b_vshader.vs", "assets/b_fshader.fs");

	// Prepare open GL for blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO); // Bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).

	// Copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	Texture2D texture1("assets/hank_texture_assignment.png", GL_NEAREST, GL_REPEAT);
	Texture2D texture2("assets/hank_fight_pose.png", GL_NEAREST, GL_REPEAT);
	Texture2D texture3("assets/bricks.jpg", GL_LINEAR, GL_REPEAT);

	ourShader.use();
	glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);

	ourShader2.use();
	glUniform1i(glGetUniformLocation(ourShader2.ID, "texture1"), 1);
	glUniform1i(glGetUniformLocation(ourShader2.ID, "texture2"), 2);

	// Render loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		double timeValue = glfwGetTime();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// -- Render the Background --
		texture2.Bind(GL_TEXTURE1);
		texture3.Bind(GL_TEXTURE2);

		ourShader2.use();
		ourShader2.setFloat("time", timeValue);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// -- Render the Character -- 
		texture1.Bind(GL_TEXTURE0);
		ourShader.use();
		ourShader.setFloat("time", timeValue);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	printf("Shutting down...");
}
