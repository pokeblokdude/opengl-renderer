#pragma once

#include <glm/vec2.hpp>

class Window {

public:
	int width, height;
	const char* title;

	Window(int width, int height, const char* title);
	~Window();

	void Tick(float deltaTime);

	bool ShouldQuit();
	void Resize(int width, int height);
	void UpdateMousePos(float x, float y);
	void UpdateScroll(float x, float y);

	glm::vec2 GetMousePos();
	glm::vec2 GetMouseDelta();
	glm::vec2 GetScrollDelta();

	struct GLFWwindow* GetRenderContext();

private:
	glm::vec2 mouseLastPos;
	glm::vec2 mousePos;
	glm::vec2 mouseDelta;
	glm::vec2 scrollDelta;
	bool mouseMoved = false;
	bool mouseScrolled = false;

	bool quit;
	struct GLFWwindow* window;

};

