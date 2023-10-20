#pragma once

#include <memory>

class Renderer {

public:

	Renderer();
	~Renderer();

	void Tick(float deltaTime);
	bool Quit();

	float cameraSpeed = 10.f;

	class Window* window;
private:
	class Shader* shader;
	std::unique_ptr<class Scene> scene;
	std::unique_ptr<class Camera> camera;

	uint32_t texture, texture2;

	void ImportObject();
	void ProcessInput(struct GLFWwindow* window, float deltaTime);

	void DrawUI(float deltaTime);
	void Clear();

	bool doCameraMovement = false;
	bool wireframe = false;
};