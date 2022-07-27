#pragma once

#include <vector>

#include "oglm.hpp"

class Cube {
  private:
	std::vector<oglm::vec3> points;
	std::vector<oglm::vec2i> indices;
	unsigned int thickness;
	unsigned int frameCount;

  public:
	Cube();
	void draw();
	void animate();
	void translate(float x, float y, float z);
	void translate(oglm::vec3f factor);
	void rotate(float angle, float x, float y, float z);
	void rotate(float angle, oglm::vec3 factor);
	void scale(float x, float y, float z);
	void scale(oglm::vec3 factor);
	bool isCompleted();
	void pause();
	void reset();
	void increaseSpeed(int speed);
	void decreaseSpeed(int speed);
	~Cube();
};
