#pragma once
class Window
{
public:
	int width, height;
	const char* title;

	Window(int width, int height, const char* title);
	~Window();

	void PollEvents();
	bool ShouldQuit();

	void Resize(int width, int height);

	struct GLFWwindow* GetRenderContext();

private:
	bool quit;
	struct GLFWwindow* window;
};

