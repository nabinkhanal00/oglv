// Include GLFW

#include <iostream>

#include "ResourceManager.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "Renderer.hpp"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

#include <GLFW/glfw3.h>

const unsigned int WIDTH = 728;
const unsigned int HEIGHT = 728;

GLFWwindow *InitWindow() {
	// Initialise GLFW
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return nullptr;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,
	               GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwSwapInterval(1);

	// Open a window and create its OpenGL context
	GLFWwindow *window =
	    glfwCreateWindow(WIDTH, HEIGHT, "opengl-Red triangle", NULL, NULL);
	if (window == NULL) {
		fprintf(
		    stderr,
		    "Failed to open GLFW window. If you have an Intel GPU, they are "
		    "not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(window);

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Unable to laod GLAD" << std::endl;
	}

	std::cout << "Using GL Version: " << glGetString(GL_VERSION) << std::endl;

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	return window;
}

int main(void) {
	GLFWwindow *window = InitWindow();
	if (!window)
		return -1;

	float vertices[] = {
	    0.5f,  0.5f,  0.0f, // top right
	    0.5f,  -0.5f, 0.0f, // bottom right
	    -0.5f, -0.5f, 0.0f, // bottom left
	    -0.5f, 0.5f,  0.0f  // top left
	};

	unsigned int indices[] = {0, 1, 2, 2, 3, 0};
	VertexArray va;
	VertexBuffer vb(vertices, 4 * 3 * sizeof(float));
	IndexBuffer ib(indices, 6);

	VertexBufferLayout layout;
	layout.AddFloat(3);

	va.AddBuffer(vb, layout);

	Shader shader =
	    ResourceManager::LoadShader("res/shaders/basic-vertex.glsl",
	                                "res/shaders/basic-fragment.glsl", "basic");

	shader.Use();

	Renderer renderer;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	while (glfwWindowShouldClose(window) == false) {

		renderer.Clear();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		renderer.Draw(va, ib, shader, GL_TRIANGLES);
		// render your GUI
		ImGui::Begin("window");
		ImGui::Button("Hello!");
		ImGui::End();

		// Render dear imgui into screen
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
