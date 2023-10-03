#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include <iostream>

#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

int main() {

	Renderer renderer;

	// RENDER LOOP
	float deltaTime = 0;
	while (!renderer.Quit()) {
		float t = glfwGetTime();

		renderer.Tick(deltaTime);

		//std::cout << 1 / deltaTime << " fps / " << deltaTime * 1000 << " ms" << std::endl;

		deltaTime = glfwGetTime() - t;
	}

	return 0;
}