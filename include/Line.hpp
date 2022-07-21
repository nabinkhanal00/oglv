#pragma once

#include "oglm.hpp"
#include "Angel.hpp"
#include <vector>
class Line {
  private:
	std::vector<oglm::vec2i> points;
	std::vector<oglm::vec2i> false_points;
	unsigned int thickness;
	unsigned int frameCount;

  public:
	Line(int x1, int y1, int x2, int y2, unsigned int thickness = 1);
	void draw();
	void animate();
	void translate(int x, int y);
	void translate(oglm::vec2i factor);
	void rotate(int radians, int x, int y);
	void rotate(int radians, oglm::vec2i factor);
	void scale(int x, int y);
	void scale(oglm::vec2i factor);
	bool isCompleted();
	void pause();
	void reset();
	void increaseSpeed(int speed);
	void decreaseSpeed(int speed);
};
