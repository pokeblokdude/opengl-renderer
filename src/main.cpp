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

		//std::cout << "---> NEW FRAME" << std::endl;

		renderer.Tick(deltaTime);

		deltaTime = glfwGetTime() - t;
	}

	return 0;
}