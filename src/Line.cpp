#include "Line.hpp"
#include "Angel.hpp"
#include <iostream>

Line::Line(float xa, float ya, float xb, float yb, unsigned int t)
    : thickness(t), frameCount(60) {
	auto point0 = Angel::map(xa, ya);
	auto point1 = Angel::map(xb, yb);
	int x0 = point0.x;
	int y0 = point0.y;
	int xl = point1.x;
	int yl = point1.y;

	int delx = std::abs(xl - x0);
	int dely = std::abs(yl - y0);
	int a = 0, b = 0;
	int p = 0;
	a = ((xl - x0) > 0) ? thickness : -thickness;
	b = ((yl - y0) > 0) ? thickness : -thickness;
	int tempx = x0, tempy = y0;
	if (delx > dely) {
		p = 2 * dely - delx;
		for (int i = 0; i <= delx; i += thickness) {
			points.push_back(Angel::demap(x0, y0));
			false_points.push_back(Angel::demap(tempx, tempy));
			x0 += a;
			tempx += a;
			if (p <= 0) {
				p += 2 * dely;
				tempy = y0 + b;
			} else {
				p += 2 * dely - 2 * delx;
				tempy = y0;
				y0 += b;
			}
		}
	} else {
		p = 2 * delx - dely;
		for (int i = 0; i <= dely; i += thickness) {
			points.push_back(Angel::demap(x0, y0));
			false_points.push_back(Angel::demap(tempx, tempy));
			y0 += b;
			tempy += b;
			if (p <= 0) {
				tempx = x0 + a;
				p += 2 * delx;
			} else {
				p += 2 * delx - 2 * dely;
				tempx = x0;
				x0 += a;
			}
		}
	}
}

void Line::draw() {
	for (auto &i : points) {
		Angel::putPixel(i.x, i.y, thickness);
	}
}
void Line::animate() {
	static int count = 0;
	static int i = 0;
	static int stuck = 0;

	int cur;
	for (cur = 0; cur < i; cur++) {
		Angel::putPixel(points[cur].x, points[cur].y, thickness);
	}
	Angel::putPixel(points[points.size() - 1].x, points[points.size() - 1].y,
	                thickness);
	if ((i + 1) < points.size()) {
		if (stuck > 30) {
			if (int(count / 10 + 4) % 2 == 0) {
				Angel::putPixel(points[i].x, points[i].y, thickness,
				                Color(1.0f, 0.0f, 1.0f, 1.0f));
			} else {
				Angel::putPixel(false_points[i].x, false_points[i].y, thickness,
				                Color(0.0f, 0.0f, 1.0f, 1.0f));
			}
		} else {
			if (cur > 0) {
				Angel::putPixel(points[cur - 1].x, points[cur - 1].y, thickness,
				                Color(1.0f, 0.0f, 0.0f, 1.0f));
			}
		}
	}
	if (i < points.size()) {
		if (count >= frameCount) {
			stuck = 0;
			i++;
			count = 0;
		} else {
			count++;
			stuck++;
		}
	}
}
void Line::translate(float x, float y) {}
void Line::translate(oglm::vec2 factor) {}
void Line::rotate(float radians, float x, float y) {}
void Line::rotate(float radians, oglm::vec2 factor) {}
void Line::scale(float x, float y) {}
void Line::scale(oglm::vec2 factor) {}
bool Line::isCompleted() { return false; }
void Line::pause() {}
void Line::reset() {}
void Line::increaseSpeed(float speed) {}
void Line::decreaseSpeed(float speed) {}
