#pragma once

#include "Angel.hpp"
#include "oglm.hpp"
#include <vector>
class Circle {
  private:
	std::vector<oglm::vec2<int>> points;
	std::vector<oglm::vec2<int>> false_points;
	unsigned int thickness;
	unsigned int frameCount;
	int centerX;
	int centerY;
	int radius;

  public:
	Circle(int x0, int y0, int r, unsigned int thickness);
	void draw();
	void animate();
	void translate(int x, int y);
	void translate(oglm::vec2<int> factor);
	void rotate(int radians, int x, int y);
	void rotate(int radians, oglm::vec2<int> factor);
	void scale(int x, int y);
	void scale(oglm::vec2<int> factor);
	bool isCompleted();
	void pause();
	void reset();
	void increaseSpeed(int speed);
	void decreaseSpeed(int speed);
};
