#include "Cube.hpp"
#include "glad/glad.h"
#include "ResourceManager.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Context.hpp"
#include "Camera.hpp"

float Cube::vertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  0.0f,  0.0f,  -1.0f, 0.5f,  -0.5f,
    -0.5f, 1.0f,  0.0f,  0.0f,  0.0f,  -1.0f, 0.5f,  0.5f,  -0.5f, 1.0f,
    1.0f,  0.0f,  0.0f,  -1.0f, 0.5f,  0.5f,  -0.5f, 1.0f,  1.0f,  0.0f,
    0.0f,  -1.0f, -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f,  -1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  0.0f,  0.0f,  -1.0f,

    -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  0.0f,  0.0f,  1.0f,  0.5f,  -0.5f,
    0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,  0.5f,  0.5f,  0.5f,  1.0f,
    1.0f,  0.0f,  0.0f,  1.0f,  0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  -0.5f, 0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  0.0f,  0.0f,  1.0f,

    -0.5f, 0.5f,  0.5f,  1.0f,  0.0f,  -1.0f, 0.0f,  0.0f,  -0.5f, 0.5f,
    -0.5f, 1.0f,  1.0f,  -1.0f, 0.0f,  0.0f,  -0.5f, -0.5f, -0.5f, 0.0f,
    1.0f,  -1.0f, 0.0f,  0.0f,  -0.5f, -0.5f, -0.5f, 0.0f,  1.0f,  -1.0f,
    0.0f,  0.0f,  -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  -1.0f, 0.0f,  0.0f,
    -0.5f, 0.5f,  0.5f,  1.0f,  0.0f,  -1.0f, 0.0f,  0.0f,

    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.5f,  0.5f,
    -0.5f, 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  0.5f,  -0.5f, -0.5f, 0.0f,
    1.0f,  1.0f,  0.0f,  0.0f,  0.5f,  -0.5f, -0.5f, 0.0f,  1.0f,  1.0f,
    0.0f,  0.0f,  0.5f,  -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f,  1.0f,  0.0f,  -1.0f, 0.0f,  0.5f,  -0.5f,
    -0.5f, 1.0f,  1.0f,  0.0f,  -1.0f, 0.0f,  0.5f,  -0.5f, 0.5f,  1.0f,
    0.0f,  0.0f,  -1.0f, 0.0f,  0.5f,  -0.5f, 0.5f,  1.0f,  0.0f,  0.0f,
    -1.0f, 0.0f,  -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  0.0f,  -1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f,  1.0f,  0.0f,  -1.0f, 0.0f,

    -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  1.0f,  0.0f,  0.5f,  0.5f,
    -0.5f, 1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  1.0f,
    0.0f,  0.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  1.0f,  0.0f};

Cube::Cube() : shininess(32.0f), color(glm::vec3(1.0f, 0.0f, 0.0f)) {
	unsigned int VAO;
	unsigned int VBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
	                      (void *)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
	                      (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
	                      (void *)(5 * sizeof(float)));
	m_vid = VAO;
	glBindVertexArray(0);

	rotate = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));

	translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.0f));

	scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	ResourceManager::LoadShader("shaders/cube/vertex.glsl",
	                            "shaders/cube/fragment.glsl", "cube");
	Shader &shader = ResourceManager::GetShader("cube");
	shader.Bind();
	shader.SetVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.SetVec3("objectColor", glm::vec3(1.0f, 0.0f, 0.0f));
	shader.Unbind();
}
float lightPosAngle = 0.0f;
void Cube::draw(std::vector<Light> &lights) {
	rotate = glm::rotate(rotate, 0.001f, glm::vec3(1.0f, 0.0f, 0.0f));

	Shader &shader = ResourceManager::GetShader("cube");
	glm::mat4 modelMatrix = translate * rotate * scale;
	glm::mat4 viewMatrix = Context::cam.GetViewMatrix();

	shader.Bind();
	shader.SetMat4("model", modelMatrix);
	shader.SetMat4("view", viewMatrix);
	shader.SetMat4("projection", Context::projectionMatrix);
	shader.SetInt("noOfLights", lights.size());
	shader.SetVec3("viewPos", Context::cam.GetPosition());
	shader.SetVec3("color", color);
	shader.SetFloat("shininess", shininess);

	for (int i = 0; i < lights.size(); i++) {
		std::string structName = "lights[" + std::to_string(i) + "].";
		shader.SetVec3(structName + "position", lights[i].position);
		shader.SetBool(structName + "isDirLight", lights[i].isDirLight);
		shader.SetVec3(structName + "direction", lights[i].direction);
		shader.SetFloat(structName + "constant", lights[i].constant);
		shader.SetFloat(structName + "linear", lights[i].linear);
		shader.SetFloat(structName + "quadratic", lights[i].quadratic);
		shader.SetBool(structName + "isSpotLight", lights[i].isSpotlight);
		shader.SetFloat(structName + "cutOff", lights[i].cutoff);
		shader.SetFloat(structName + "outerCutOff", lights[i].outerCutOff);
		shader.SetVec3(structName + "ambient", lights[i].ambient);
		shader.SetVec3(structName + "diffuse", lights[i].diffuse);
		shader.SetVec3(structName + "specular", lights[i].specular);
	}

	glBindVertexArray(m_vid);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	shader.Unbind();
}
