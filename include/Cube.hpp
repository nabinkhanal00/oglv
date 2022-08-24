#pragma once

#include "glm/glm.hpp"
#include <vector>
#include "Light.hpp"

class Cube
{
private:
	static float vertices[];
	unsigned int m_vid;
	float shininess;
	glm::vec3 color;

public:
	Cube();
	struct props
	{
		glm::vec3 ambient, diffuse, specular;
	};
	unsigned int id;
	glm::mat4 translate, rotate, scale;
	props prop;
	void draw(std::vector<Light> &lights);
};