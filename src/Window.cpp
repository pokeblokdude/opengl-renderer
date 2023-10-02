#include "Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

Window::Window(int width, int height, const char* title) {
	this->width = width;
	this->height = height;
	this->title = title;
	quit = false;

	// init GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create window
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	

	// load all OpenGL functions with GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
}

Window::~Window() {
	glfwTerminate();
}

void Window::PollEvents() {
	glfwPollEvents();
	processInput(window);
}

bool Window::ShouldQuit() {
	return glfwWindowShouldClose(window);
}

void Window::Resize(int width, int height) {
	glViewport(0, 0, width, height);
}

GLFWwindow* Window::GetRenderContext() {
	return window;
}