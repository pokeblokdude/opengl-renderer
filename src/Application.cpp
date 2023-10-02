#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "Shader.h"
#include "stb_image.h"
#include "Window.h"
#include "Renderer.h"

int main() {

	Renderer renderer;

	// RENDER LOOP
	float deltaTime = 0;
	while (!renderer.Quit()) {
		float t = glfwGetTime();

		renderer.Tick(deltaTime);
		
		std::cout << 1/deltaTime << " fps / " << deltaTime * 1000 << " ms" << std::endl;
		
		deltaTime = glfwGetTime() - t;
	}

	return 0;
}