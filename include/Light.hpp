#pragma once

#include "glm/glm.hpp"

struct Light
{
	glm::vec3 pos;
	glm::vec3 color;
	glm::vec3 attenuation; // constant, linear, exponential

	bool isSpotlight;
	glm::vec3 direction;

	float cutoff;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};