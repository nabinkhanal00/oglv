#pragma once

#include "oglm.hpp"

class Shape2D {

  public:
	virtual void draw() = 0;
	virtual void animate() = 0;
	virtual void translate(int x, int y) = 0;
	virtual void translate(oglm::vec2<int> factor) = 0;
	virtual void rotate(int radians, int x, int y) = 0;
	virtual void rotate(int radians, oglm::vec2<int> factor) = 0;
	virtual void scale(int x, int y) = 0;
	virtual void scale(oglm::vec2<int> factor) = 0;
	virtual bool isCompleted() = 0;
	virtual void pause() = 0;
	virtual void reset() = 0;
	virtual void increaseSpeed(int speed) = 0;
	virtual void decreaseSpeed(int speed) = 0;
	virtual ~Shape2D() {}
};
