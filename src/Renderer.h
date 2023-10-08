#pragma once

#include <memory>

class Renderer {

public:

	Renderer();
	~Renderer();

	void Tick(float deltaTime);
	bool Quit();

	float cameraSpeed = 10.f;

private:
	class Window* window;
	std::unique_ptr<class Shader> shader;
	std::unique_ptr<class Scene> scene;
	std::unique_ptr<class Camera> camera;

	uint32_t texture, texture2;

	void Clear();
	void Draw(class Mesh* mesh, class Transform transform);

	void ProcessInput(class GLFWwindow* window, float deltaTime);
};