#include "Tracer.hpp"
#include "glad/glad.h"
#include "ResourceManager.hpp"
#include "Context.hpp"
#include <GLFW/glfw3.h>

Tracer::Tracer() {

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	float vertices[]{-1.0f, -1.0f, 0.0f, //
	                 -1.0f, 1.0f,  0.0f, //
	                 1.0f,  1.0f,  0.0f, //
	                 1.0f,  1.0f,  0.0f, //
	                 1.0f,  -1.0f, 0.0f, //
	                 -1.0f, -1.0,  0.0f};

	// setup vertex array buffer
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	m_id = VAO;

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
	                      (void *)0);
	glEnableVertexAttribArray(0);
}

void Tracer::draw() {
	Shader &shader = ResourceManager::GetShader("tracer");
	shader.Bind();
	shader.SetVec2("u_resolution", glm::vec2(Context::width, Context::height));
	shader.SetVec2("u_mouse", Context::mousePos);
	shader.SetFloat("u_time", glfwGetTime());
	glBindVertexArray(m_id);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	shader.Unbind();
}
