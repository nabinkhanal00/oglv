#include "Cube.hpp"
#include "glad/glad.h"
#include "ResourceManager.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Context.hpp"
#include "Camera.hpp"

float Cube::vertices[] = {
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};

Cube::Cube() : prop{0.2, 0.2, 0.2}
{
	unsigned int VAO;
	unsigned int VBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
						  (void *)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
						  (void *)(3 * sizeof(float)));
	m_vid = VAO;
	glBindVertexArray(0);

	rotate = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));

	translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.0f));

	scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	ResourceManager::LoadShader("shaders/cube/vertex.glsl",
								"shaders/cube/fragment.glsl", "cube");
}
void Cube::draw(const glm::mat4 &viewMatrix)
{

	Camera c;
	glm::mat4 vMatrix = c.GetViewMatrix();
	rotate = glm::rotate(rotate, 0.001f, glm::vec3(1.0f, 0.0f, 0.0f));

	Shader &shader = ResourceManager::GetShader("cube");
	glm::mat4 modelMatrix = translate * rotate * scale;
	shader.Bind();
	shader.SetMat4("model", modelMatrix);
	shader.SetMat4("view", viewMatrix);
	shader.SetMat4("projection", Context::projectionMatrix);
	glBindVertexArray(m_vid);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	shader.Unbind();
}
