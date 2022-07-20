#include "Line.hpp"
#include "Circle.hpp"
#include "Color.hpp"
#include <iostream>
Circle::Circle(int x0, int y0, int r, unsigned int t)
    : thickness(t), frameCount(60) {
	centerX = x0;
	centerY = y0;
	radius = r;
	int x = 0, y = r;
	int p = 1 - r;
	int tempx = x, tempy = y;
	while (y >= x) {
		points.push_back(oglm::vec2<int>(x, y));
		false_points.push_back(oglm::vec2<int>(tempx, tempy));
		bool visited = false;
		if (p >= 0) {
			tempy = y;
			y -= thickness;
			p -= 2 * y;
			visited = true;
		}
		if (!visited) {
			tempy = y - thickness;
		}
		x += thickness;
		tempx = x;
		p += 2 * x + 1;
	}
}

void Circle::draw() {

	for (auto &i : points) {
		Angel::putPixel(i.x + centerX, i.y + centerY, thickness);
		Angel::putPixel(i.y + centerX, i.x + centerY, thickness);
		Angel::putPixel(-i.x + centerX, i.y + centerY, thickness);
		Angel::putPixel(-i.y + centerX, i.x + centerY, thickness);
		Angel::putPixel(i.x + centerX, -i.y + centerY, thickness);
		Angel::putPixel(i.y + centerX, -i.x + centerY, thickness);
		Angel::putPixel(-i.x + centerX, -i.y + centerY, thickness);
		Angel::putPixel(-i.y + centerX, -i.x + centerY, thickness);
	}
}

void Circle::animate() {
	static int count = 0;
	static int i = 0;
	static int stuck = 0;
	int cur;
	Line l1(-Angel::getWidth(), -Angel::getHeight(), Angel::getWidth(),
	        Angel::getHeight(), 1);
	l1.draw();
	Line l2(-Angel::getWidth(), Angel::getHeight(), Angel::getWidth(),
	        -Angel::getHeight(), 1);
	l2.draw();
	for (cur = 0; cur < i; cur++) {
		Angel::putPixel(points[cur].x + centerX, points[cur].y + centerY,
		                thickness);
	}

	if ((i + 1) < points.size()) {
		if (stuck > 30) {
			if (int(count / 10) % 2 == 0) {
				Angel::putPixel(points[i].x + centerX, points[i].y + centerY,
				                thickness, Color(1.0f, 0.0f, 1.0f, 1.0f));
			} else {
				Angel::putPixel(false_points[i].x + centerX,
				                false_points[i].y + centerY, thickness,
				                Color(0.0f, 0.0f, 1.0f, 1.0f));
			}
		} else {
			if (cur > 0) {
				Angel::putPixel(points[cur - 1].x + centerX,
				                points[cur - 1].y + centerY, thickness,
				                Color(1.0f, 0.0f, 0.0f, 1.0f));
			}
		}
	}
	for (cur = 0; cur < i; cur++) {
		Angel::putPixel(points[cur].y + centerX, points[cur].x + centerY,
		                thickness);
	}
	if ((i + 1) < points.size()) {
		if (stuck > 30) {
			if (int(count / 10) % 2 == 0) {
				Angel::putPixel(points[i].y + centerX, points[i].x + centerY,
				                thickness, Color(1.0f, 0.0f, 1.0f, 1.0f));
			} else {
				Angel::putPixel(false_points[i].y + centerX,
				                false_points[i].x + centerY, thickness,
				                Color(0.0f, 0.0f, 1.0f, 1.0f));
			}
		} else {
			if (cur > 0) {
				Angel::putPixel(points[cur - 1].y + centerX,
				                points[cur - 1].x + centerY, thickness,
				                Color(1.0f, 0.0f, 0.0f, 1.0f));
			}
		}
	}
	for (cur = 0; cur < i; cur++) {
		Angel::putPixel(-points[cur].x + centerX, points[cur].y + centerY,
		                thickness);
	}
	if ((i + 1) < points.size()) {
		if (stuck > 30) {
			if (int(count / 10) % 2 == 0) {
				Angel::putPixel(-points[i].x + centerX, points[i].y + centerY,
				                thickness, Color(1.0f, 0.0f, 1.0f, 1.0f));
			} else {
				Angel::putPixel(-false_points[i].x + centerX,
				                false_points[i].y + centerY, thickness,
				                Color(0.0f, 0.0f, 1.0f, 1.0f));
			}
		} else {
			if (cur > 0) {
				Angel::putPixel(-points[cur - 1].x + centerX,
				                points[cur - 1].y + centerY, thickness,
				                Color(1.0f, 0.0f, 0.0f, 1.0f));
			}
		}
	}
	for (cur = 0; cur < i; cur++) {
		Angel::putPixel(-points[cur].y + centerX, points[cur].x + centerY,
		                thickness);
	}
	if ((i + 1) < points.size()) {
		if (stuck > 30) {
			if (int(count / 10) % 2 == 0) {
				Angel::putPixel(-points[i].y + centerX, points[i].x + centerY,
				                thickness, Color(1.0f, 0.0f, 1.0f, 1.0f));
			} else {
				Angel::putPixel(-false_points[i].y + centerX,
				                false_points[i].x + centerY, thickness,
				                Color(0.0f, 0.0f, 1.0f, 1.0f));
			}
		} else {
			if (cur > 0) {
				Angel::putPixel(-points[cur - 1].y + centerX,
				                points[cur - 1].x + centerY, thickness,
				                Color(1.0f, 0.0f, 0.0f, 1.0f));
			}
		}
	}

	for (cur = 0; cur < i; cur++) {
		Angel::putPixel(points[cur].x + centerX, -points[cur].y + centerY,
		                thickness);
	}
	if ((i + 1) < points.size()) {
		if (stuck > 30) {
			if (int(count / 10) % 2 == 0) {
				Angel::putPixel(points[i].x + centerX, -points[i].y + centerY,
				                thickness, Color(1.0f, 0.0f, 1.0f, 1.0f));
			} else {
				Angel::putPixel(false_points[i].x + centerX,
				                -false_points[i].y + centerY, thickness,
				                Color(0.0f, 0.0f, 1.0f, 1.0f));
			}
		} else {
			if (cur > 0) {
				Angel::putPixel(points[cur - 1].x + centerX,
				                -points[cur - 1].y + centerY, thickness,
				                Color(1.0f, 0.0f, 0.0f, 1.0f));
			}
		}
	}
	for (cur = 0; cur < i; cur++) {
		Angel::putPixel(points[cur].y + centerX, -points[cur].x + centerY,
		                thickness);
	}
	if ((i + 1) < points.size()) {
		if (stuck > 30) {
			if (int(count / 10) % 2 == 0) {
				Angel::putPixel(points[i].y + centerX, -points[i].x + centerY,
				                thickness, Color(1.0f, 0.0f, 1.0f, 1.0f));
			} else {
				Angel::putPixel(false_points[i].y + centerX,
				                -false_points[i].x + centerY, thickness,
				                Color(0.0f, 0.0f, 1.0f, 1.0f));
			}
		} else {
			if (cur > 0) {
				Angel::putPixel(points[cur - 1].y + centerX,
				                -points[cur - 1].x + centerY, thickness,
				                Color(1.0f, 0.0f, 0.0f, 1.0f));
			}
		}
	}
	for (cur = 0; cur < i; cur++) {
		Angel::putPixel(-points[cur].x + centerX, -points[cur].y + centerY,
		                thickness);
	}
	if ((i + 1) < points.size()) {
		if (stuck > 30) {
			if (int(count / 10) % 2 == 0) {
				Angel::putPixel(-points[i].x + centerX, -points[i].y + centerY,
				                thickness, Color(1.0f, 0.0f, 1.0f, 1.0f));
			} else {
				Angel::putPixel(-false_points[i].x + centerX,
				                -false_points[i].y + centerY, thickness,
				                Color(0.0f, 0.0f, 1.0f, 1.0f));
			}
		} else {
			if (cur > 0) {
				Angel::putPixel(-points[cur - 1].x + centerX,
				                -points[cur - 1].y + centerY, thickness,
				                Color(1.0f, 0.0f, 0.0f, 1.0f));
			}
		}
	}
	for (cur = 0; cur < i; cur++) {
		Angel::putPixel(-points[cur].y + centerX, -points[cur].x + centerY,
		                thickness);
	}
	if ((i + 1) < points.size()) {
		if (stuck > 30) {
			if (int(count / 10) % 2 == 0) {
				Angel::putPixel(-points[i].y + centerX, -points[i].x + centerY,
				                thickness, Color(1.0f, 0.0f, 1.0f, 1.0f));
			} else {
				Angel::putPixel(-false_points[i].y + centerX,
				                -false_points[i].x + centerY, thickness,
				                Color(0.0f, 0.0f, 1.0f, 1.0f));
			}
		} else {
			if (cur > 0) {
				Angel::putPixel(-points[cur - 1].y + centerX,
				                -points[cur - 1].x + centerY, thickness,
				                Color(1.0f, 0.0f, 0.0f, 1.0f));
			}
		}
	}
	if (i < points.size()) {
		if (count >= frameCount) {
			i++;
			count = 0;
			stuck = 0;
		} else {
			count++;
			stuck++;
		}
	}
};
void Circle::translate(int x, int y){};
void Circle::translate(oglm::vec2<int> factor){};
void Circle::rotate(int radians, int x, int y){};
void Circle::rotate(int radians, oglm::vec2<int> factor){};
void Circle::scale(int x, int y){};
void Circle::scale(oglm::vec2<int> factor){};
bool Circle::isCompleted() { return true; };
void Circle::pause(){};
void Circle::reset(){};
void Circle::increaseSpeed(int speed){};
void Circle::decreaseSpeed(int speed){};
