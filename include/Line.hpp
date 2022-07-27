#pragma once

#include "oglm.hpp"
#include "Angel.hpp"
#include <vector>
class Line {
  private:
	std::vector<oglm::vec2> points;
	std::vector<oglm::vec3> points3D;
	std::vector<oglm::vec2> false_points;
	unsigned int thickness;
	unsigned int frameCount;

  public:
	Line(float x1, float y1, float x2, float y2, unsigned int thickness = 1);
	Line(float x1, float y1, float z1, float x2, float y2, float z2,
	     unsigned int thickness = 1);
	void draw();
	void draw3D();
	void show_points();
	void animate();
	void translate(float x, float y);
	void translate(oglm::vec2 factor);
	void rotate(float radians, float x, float y);
	void rotate(float radians, oglm::vec2 factor);
	void scale(float x, float y);
	void scale(oglm::vec2 factor);
	bool isCompleted();
	void pause();
	void reset();
	void increaseSpeed(float speed);
	void decreaseSpeed(float speed);
};
