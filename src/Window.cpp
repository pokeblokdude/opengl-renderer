#include "Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

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

	// turn off vsync
	glfwSwapInterval(0);
	
	// set window pointer (get with glfwGetWindowUserPointer())
	glfwSetWindowUserPointer(window, this);

	// set resize callback
	auto resize = [](GLFWwindow* window, int width, int height) {
		static_cast<Window*>(glfwGetWindowUserPointer(window))->Resize(width, height);
		glViewport(0, 0, width, height);
	};
	glfwSetFramebufferSizeCallback(window, resize);

	//set mouse move callback
	auto mouseMove = [](GLFWwindow* window, double posx, double posy) {
		static_cast<Window*>(glfwGetWindowUserPointer(window))->UpdateMousePos(posx, posy);
	};
	glfwSetCursorPosCallback(window, mouseMove);

	if (glfwRawMouseMotionSupported()) {
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	}

	// load all OpenGL functions with GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	// setup ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 410");
}

Window::~Window() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
}

void Window::Tick(float deltaTime) {
	if (mouseMoved) {
		mouseMoved = false;
	}
	else {
		mouseDelta = { 0, 0 };
	}
}

bool Window::ShouldQuit() {
	return glfwWindowShouldClose(window);
}

void Window::Resize(int width, int height) {
	this->width = width;
	this->height = height;
}

void Window::UpdateMousePos(float x, float y) {
	mousePos = { x, y };
	mouseDelta = mousePos - mouseLastPos;
	mouseLastPos = mousePos;
	mouseMoved = true;
}

glm::vec2 Window::GetMousePos() {
	return mousePos;
}

glm::vec2 Window::GetMouseDelta() {
	return mouseDelta;
}

GLFWwindow* Window::GetRenderContext() {
	return window;
}