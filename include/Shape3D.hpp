#pragma once

#include "oglm/oglm.hpp"

class Shape3D {
  public:
	virtual void draw() = 0;
	virtual void animate() = 0;
	virtual void translate(float x, float y, float z) = 0;
	virtual void translate(oglm::vec3<float> factor) = 0;
	virtual void rotate(float radians, float x, float y, float z);
	virtual void rotate(float radians, oglm::vec3<float> factor);
	virtual void scale(float x, float y, float z);
	virtual void scale(oglm::vec3<float> factor);

	virtual bool isCompleted() = 0;
	virtual void pause() = 0;
	virtual void reset() = 0;
	virtual void increaseSpeed(float speed) = 0;
	virtual void decreaseSpeed(float speed) = 0;
};
