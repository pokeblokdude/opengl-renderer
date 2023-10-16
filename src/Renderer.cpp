#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include <vector>
#include "Shader.h"
#include "stb_image.h"
#include "world/model/primitives/Cube.h"
#include "world/model/primitives/Quad.h"
#include <glm/gtc/type_ptr.hpp>
#include "Window.h"
#include "world/Scene.h"
#include "world/model/Mesh.h"
#include "world/Camera.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

Renderer::Renderer() {

	window = new Window(1920, 1080, "OpenGL Renderer");

	shader = std::make_unique<Shader>("src/shaders/vertex.glsl", "src/shaders/fragment.glsl");

	scene = std::make_unique<Scene>();
	camera = std::make_unique<Camera>(50, (window->width/(float)window->height), 0.001f, 1000);
	camera->transform.position.z = 10;

	Object* cube = new Object();
	cube->name = "Cube 0";
	cube->mesh = new Cube();
	//cube->transform.rotation.y = 45;

	scene->objects.push_back(cube);

	Object* cube1 = new Object();
	cube1->name = "Cube 1";
	cube1->mesh = new Cube();
	cube1->transform.position.y = 1.5f;
	cube1->transform.position.x = 1.5f;
	cube1->transform.rotation.y = -20;
	cube1->transform.rotation.x = 35;

	scene->objects.push_back(cube1);

	Object* quad = new Object();
	quad->name = "Quad";
	quad->mesh = new Quad();
	quad->transform.position.x = -1.5f;
	quad->transform.position.y = 2.0f;
	quad->transform.rotation.z = 40.f;
	quad->transform.rotation.x = 10.f;

	scene->objects.push_back(quad);

	glGenTextures(1, &texture);
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

	/*glGenTextures(1, &texture2);
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

	glEnable(GL_DEPTH_TEST);
}

Renderer::~Renderer() {
	delete window;
}

void Renderer::Tick(float deltaTime) {
	// poll inputs
	glfwPollEvents();
	ProcessInput(window->GetRenderContext(), deltaTime);
	window->Tick(deltaTime);

	// update scene
	scene->objects[0]->transform.rotation.y += 10 * deltaTime;
	scene->objects[0]->transform.rotation.x += 10 * deltaTime;

	// actual rendering
	camera->Resize(window->width / (float)window->height);
	glm::vec2 look = window->GetMouseDelta();
	if (doCameraMovement) {
		camera->transform.rotation.y += look.x * 100 * deltaTime;
		camera->transform.rotation.x += look.y * 100 * deltaTime;
		camera->transform.rotation.x = glm::clamp(camera->transform.rotation.x, -90.f, 90.f);
	}

	// setup ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	
	DrawUI(deltaTime);

	// clear framebuffer
	Clear();

	// set draw mode to wireframe
	if (wireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glDisable(GL_CULL_FACE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);
	}


	for (Object* obj : scene->objects) {
		if (obj->mesh != nullptr) {
			Draw(obj->mesh, obj->transform);
		}
	}

	// render ImGui frame
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// show final render
	glfwSwapBuffers(window->GetRenderContext());
}

bool Renderer::Quit() {
	return window->ShouldQuit();
}

void Renderer::Clear() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(Mesh* mesh, Transform transform) {

	shader->SetActive();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, texture2);

	glm::mat4 M = transform.Matrix();
	glm::mat4 V = camera->ViewMatrix();
	glm::mat4 P = camera->ProjectionMatrix();

	glm::mat4 MVP = P * V * M;
	glm::mat4 MV = V * M;
	glUniformMatrix4fv(glGetUniformLocation(shader->ID, "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
	glUniformMatrix4fv(glGetUniformLocation(shader->ID, "MV"), 1, GL_FALSE, glm::value_ptr(MV));
	glUniformMatrix4fv(glGetUniformLocation(shader->ID, "view"), 1, GL_FALSE, glm::value_ptr(V));

	glm::vec3 cam = camera->transform.Forward();
	glUniform3fv(glGetUniformLocation(shader->ID, "camVector"), 1, (float*)&cam);

	glBindVertexArray(mesh->VertexArrayObject());
	glDrawElements(GL_TRIANGLES, mesh->faces.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void Renderer::DrawUI(float deltaTime) {
	// menu bar
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("New Scene", "Ctrl+N")) {

			}
			if (ImGui::MenuItem("Open", "Ctrl+O")) {

			}
			ImGui::Separator();
			if (ImGui::MenuItem("Quit", "Alt+F4")) {
				glfwSetWindowShouldClose(window->GetRenderContext(), true);
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	// debug window
	ImGui::Begin("Debug Window");
	ImGui::Text("%.2f fps / %f ms", 1 / deltaTime, deltaTime);
	ImGui::Text("Frame Size: %ix%i (%.3f:1)", window->width, window->height, camera->aspect);
	ImGui::SeparatorText("Mouse");
	glm::vec2 mpos = window->GetMousePos();
	ImGui::Text("Position: %.2f, %.2f", mpos.x, mpos.y);
	glm::vec2 look = window->GetMouseDelta();
	ImGui::Text("Delta: %.4f, %.4f", look.x, look.y);
	ImGui::SeparatorText("Camera");
	if (ImGui::Button("Reset Position")) {
		camera->ResetPosition();
	}
	ImGui::DragFloat("Speed", &cameraSpeed, 0.5f);
	ImGui::DragFloat("FOV", &camera->fov, 0.5f);
	ImGui::DragFloat3("Position", (float*)&camera->transform.position, 0.5f);
	ImGui::DragFloat3("Rotation", (float*)&camera->transform.rotation, 0.5f);
	glm::vec3 f = camera->transform.Forward();
	ImGui::Text("Looking toward: %.4f, %.4f, %.4f", f.x, f.y, f.z);
	ImGui::SeparatorText("Options");
	ImGui::Checkbox("Draw Wireframe", &wireframe);
	ImGui::End();

	//ImGui::ShowDemoWindow();

	// objects list window
	ImGui::Begin("Objects");
	for (Object* obj : scene->objects) {
		ImGui::Text(obj->name.c_str());
	}
	ImGui::End();
}

void Renderer::ProcessInput(GLFWwindow* window, float deltaTime) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	// enable camera movement when holding right click
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS) {
		doCameraMovement = true;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			camera->transform.position += camera->transform.Forward() * cameraSpeed * deltaTime;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			camera->transform.position -= camera->transform.Forward() * cameraSpeed * deltaTime;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			camera->transform.position -= camera->transform.Right() * cameraSpeed * deltaTime;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			camera->transform.position += camera->transform.Right() * cameraSpeed * deltaTime;
		}
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
			camera->transform.position -= camera->transform.Up() * cameraSpeed * deltaTime;
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
			camera->transform.position += camera->transform.Up() * cameraSpeed * deltaTime;
		}
	}
	else {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		doCameraMovement = false;
	}
	
}