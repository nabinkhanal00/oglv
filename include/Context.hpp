#pragma once
#include "glm/gtc/matrix_transform.hpp"
#include "Camera.hpp"
class Context {
  public:
	static int height;
	static int width;
	static glm::mat4 projectionMatrix;
	static Camera cam;
	static glm::vec2 mousePos;
};
