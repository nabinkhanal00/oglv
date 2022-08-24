#include "Context.hpp"

int Context::height = 1000;
int Context::width = 1000;
glm::mat4 Context::projectionMatrix = glm::perspective(glm::radians(90.0f), width / (float)height, 0.1f, 100.0f);
Camera Context::cam = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
glm::vec2 Context::mousePos = glm::vec2(0.0f,0.0f);
