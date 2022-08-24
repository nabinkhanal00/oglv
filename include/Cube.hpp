#pragma once

#include "glm/glm.hpp"

class Cube
{
private:
	static float vertices[];
	unsigned int m_vid;

public:
	Cube();
	struct props
	{
		glm::vec3 ambient, diffuse, specular;
	};
	unsigned int id;
	glm::mat4 translate, rotate, scale;
	props prop;
	void draw(const glm::mat4 &viewMatrix);
};