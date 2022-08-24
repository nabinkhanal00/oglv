#pragma once

#include "glm/glm.hpp"

struct Light {
	glm::vec3 position;
	bool isDirLight;
	glm::vec3 direction;

	float constant, linear, quadratic; // attenuation values

	bool isSpotlight;
	float cutoff;
	float outerCutOff;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};
