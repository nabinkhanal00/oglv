#pragma once

#include "glm/glm.hpp"

struct Light {
	glm::vec3 position;
	glm::vec3 color;

	glm::vec3 direction;
        float ambientStrength{0.5};
        float diffuseStrength{0.5};
        float specularStrength{0.5};
        int shininess{32};
};
