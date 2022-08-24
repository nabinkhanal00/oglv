#pragma once

#include "Angel.hpp"
#include "oglm.hpp"
#include <vector>
class Circle {
private:
  unsigned int thickness;
  unsigned int frameCount;
  int centerX;
  int centerY;
  int radius;

public:
  Circle(int x0, int y0, int r, unsigned int thickness);
  std::vector<oglm::vec2i> points;
  std::vector<oglm::vec2i> false_points;
  void draw(const oglm::vec4 &color = oglm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
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
