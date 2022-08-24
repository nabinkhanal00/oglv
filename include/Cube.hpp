#pragma once

#include "glm/glm.hpp"
#include <vector>
#include "Light.hpp"

class Cube {
  private:
	static float vertices[];
	unsigned int m_vid;

  public:
	Cube();
	struct props {
		glm::vec3 ambient, diffuse, specular;
	};
	unsigned int id;
	glm::mat4 translate, rotate, scale;
	glm::vec3 color;
	float shininess;
	glm::vec3 position;
	props prop;
	void draw();
        void draw(Light light, bool isPhong);
};
