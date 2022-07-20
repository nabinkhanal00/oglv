#pragma once

#include "oglm.hpp"

class Shape3D {
  public:
	virtual void draw() = 0;
	virtual void animate() = 0;
	virtual void translate(int x, int y, int z) = 0;
	virtual void translate(oglm::vec3<int> factor) = 0;
	virtual void rotate(int radians, int x, int y, int z);
	virtual void rotate(int radians, oglm::vec3<int> factor);
	virtual void scale(int x, int y, int z);
	virtual void scale(oglm::vec3<int> factor);

	virtual bool isCompleted() = 0;
	virtual void pause() = 0;
	virtual void reset() = 0;
	virtual void increaseSpeed(int speed) = 0;
	virtual void decreaseSpeed(int speed) = 0;

	virtual ~Shape3D();
};
