#include <iostream>
#include <cmath>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "VAO/VAO.hpp"
#include "VBO/VBO.hpp"
#include "EBO/EBO.hpp"
#include "shaders/shaderClass.hpp"
#include "Texture/Texture.hpp"
#include "Math/VEC/VEC3.hpp"
#include "Math/MAT/MAT4.hpp"

const unsigned int width = 800;
const unsigned int height = 800;

GLfloat vertices[] =
	{//     COORDINATES     /        COLORS      /   TexCoord  //
	 -0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
	 -0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
	 0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f,
	 0.0f, 0.8f, 0.0f, 0.92f, 0.86f, 0.76f, 2.5f, 5.0f};

// Indices for vertices order
GLuint indices[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		3, 0, 4};

void processInputs(GLFWwindow *window, Vec3 &objPos)
{
	float speed = 0.001f;

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		speed = 0.05f;

	// X : gauche / droite
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		objPos.x += speed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		objPos.x -= speed;

	// Y : bas / haut
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		objPos.y += speed;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		objPos.y -= speed;

	// Z : loin / proche (la caméra regarde vers -Z)
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		objPos.z += speed;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		objPos.z -= speed;
}

int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(800, 800, "Scop", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	if (!gladLoadGL(glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);

	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("src/shaders/default.vert", "src/shaders/default.frag");

	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Texture
	Texture popCat("src/assets/textures/texture.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCat.texUnit(shaderProgram, "tex0", 0);

	glEnable(GL_DEPTH_TEST);

	Vec3 objPos(0.0f, 0.0f, 0.0f);
	float angle = 0.0f;

	// View et projection : fixes, calculées une seule fois
	Mat4 view = Mat4::lookAt(Vec3(0, 0, 2), Vec3(0, 0, 0), Vec3(0, 1, 0));
	Mat4 proj = Mat4::perspective(Mat4::radians(45.0f), (float)width / height, 0.1f, 100.0f);
	GLint camLoc = glGetUniformLocation(shaderProgram.ID, "camMatrix");

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaderProgram.Activate();

		processInputs(window, objPos);
		//angle += 0.01f;

		// Model : déplacement de l'objet + rotation sur lui-même
		Mat4 model = Mat4::translate(objPos) * Mat4::rotateY(angle);
		Mat4 mvp = proj * view * model;
		glUniformMatrix4fv(camLoc, 1, GL_FALSE, mvp.m);

		popCat.Bind();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	popCat.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}