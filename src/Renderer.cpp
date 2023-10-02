#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include <vector>
#include "Shader.h"
#include "stb_image.h"
#include "world/shapes/Cube.h"
#include <glm/gtc/type_ptr.hpp>
#include "Window.h"
#include "world/Scene.h"
#include "world/Mesh.h"
#include "world/Camera.h"

Renderer::Renderer() {

	window = new Window(800, 600, "OpenGL Renderer");

	shader = std::make_unique<Shader>("src/shaders/vertex.glsl", "src/shaders/fragment.glsl");

	scene = std::make_unique<Scene>();
	camera = std::make_unique<Camera>(50, (window->width/(float)window->height), 0.001f, 1000);
	camera->transform.position.z = 10;

	glfwSetWindowUserPointer(window->GetRenderContext(), window);
	auto func = [](GLFWwindow*, int width, int height) {
		

	};

	glfwSetFramebufferSizeCallback(window->GetRenderContext(), func);

	//std::vector<float> vertices1 = {
	//	// positions          // colors           // texture coords
	//	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f,   // top right
	//	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f,   // bottom right
	//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f    // top left 
	//};
	//std::vector<uint32_t> indices1 = {
	//	0, 1, 3,
	//	1, 2, 3
	//};

	Object* cube = new Object();
	cube->mesh = new Cube();
	cube->transform.rotation.y = 45;

	scene->objects.push_back(cube);

	/*glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("res/texture.png", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	data = stbi_load("res/texture2.png", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	shader->SetActive();
	glUniform1i(glGetUniformLocation(shader->ID, "tex"), 0);
	shader->SetInt("tex2", 1);*/
}

Renderer::~Renderer() {
	delete window;
}

void Renderer::Tick(float deltaTime) {
	// poll inputs
	window->PollEvents();

	// update scene
	scene->objects[0]->transform.rotation.y += 10 * deltaTime;
	scene->objects[0]->transform.rotation.x += 10 * deltaTime;

	// actual rendering
	Clear();

	// set draw mode to wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (Object* obj : scene->objects) {
		if (obj->mesh != nullptr) {
			Draw(obj->mesh, obj->transform);
		}
	}


	glfwSwapBuffers(window->GetRenderContext());
}

bool Renderer::Quit() {
	return window->ShouldQuit();
}

void Renderer::Clear() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(Mesh* mesh, Transform transform) {

	shader->SetActive();

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, texture);
	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, texture2);

	glm::mat4 MVP = camera->ProjectionMatrix() * camera->ViewMatrix() * transform.Matrix();
	glUniformMatrix4fv(glGetUniformLocation(shader->ID, "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));

	/*glUniformMatrix4fv(glGetUniformLocation(shader->ID, "transform"), 1, GL_FALSE, glm::value_ptr(transform.Matrix()));
	glUniformMatrix4fv(glGetUniformLocation(shader->ID, "view"), 1, GL_FALSE, glm::value_ptr(camera->ViewMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(shader->ID, "projection"), 1, GL_FALSE, glm::value_ptr(camera->ProjectionMatrix()));
	*/

	glBindVertexArray(mesh->VertexArrayObject());
	glDrawElements(GL_TRIANGLES, mesh->faces.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}