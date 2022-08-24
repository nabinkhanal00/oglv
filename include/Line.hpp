#pragma once

#include "Angel.hpp"
#include "oglm.hpp"
#include <vector>

class Line
{
private:
  unsigned int thickness;

public:
  Line(float x1, float y1, float x2, float y2, unsigned int thickness = 1);
  Line(float x1, float y1, float z1, float x2, float y2, float z2,
       unsigned int thickness = 1);
  unsigned int frameCount{60};
  std::vector<oglm::vec2f> points;
  std::vector<oglm::vec3f> points3D;
  std::vector<oglm::vec2f> false_points;
  int count{0};
  int i{0};
  int stuck{0};
  float color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
  bool lineDraw = true;
  bool lineAnimate = false;
  bool startLineDrawing = false;
  void draw(const oglm::vec4 &color = {1.0f, 1.0f, 1.0f, 1.0f});
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
