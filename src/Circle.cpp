#include "Line.hpp"
#include "Circle.hpp"
#include "Color.hpp"
#include <iostream>
Circle::Circle(float x0, float y0, float r, unsigned int t)
    : thickness(t), frameCount(60) {
	centerX = x0;
	centerY = y0;
	radius = r;
	int rd = round(r * Angel::getWidth() / 2);

	int offsetX = Angel::getWidth() / 2;
	int offsetY = Angel::getHeight() / 2;
	int x = 0;
	int y = rd;
	int p = 1 - rd;
	int tempx = x, tempy = y;
	while (y >= x) {
		points.push_back(Angel::demap(x + offsetX, y + offsetY));
		false_points.push_back(Angel::demap(tempx + offsetX, tempy + offsetY));
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

void Circle::draw(const oglm::vec4 &color) {

	for (auto &i : points) {
		Angel::putPixel(i.x + centerX, i.y + centerY, thickness, color);
		Angel::putPixel(i.y + centerX, i.x + centerY, thickness, color);
		Angel::putPixel(-i.x + centerX, i.y + centerY, thickness, color);
		Angel::putPixel(-i.y + centerX, i.x + centerY, thickness, color);
		Angel::putPixel(i.x + centerX, -i.y + centerY, thickness, color);
		Angel::putPixel(i.y + centerX, -i.x + centerY, thickness, color);
		Angel::putPixel(-i.x + centerX, -i.y + centerY, thickness, color);
		Angel::putPixel(-i.y + centerX, -i.x + centerY, thickness, color);
	}
}

void Circle::animate() {
	static int count = 0;
	static int i = 0;
	static int stuck = 0;
	int cur;
	// Line l1(-Angel::getWidth(), -Angel::getHeight(), Angel::getWidth(),
	//         Angel::getHeight(), 1);
	// l1.draw();
	// Line l2(-Angel::getWidth(), Angel::getHeight(), Angel::getWidth(),
	//         -Angel::getHeight(), 1);
	// l2.draw();
	for (cur = 0; cur < i; cur++) {
		Angel::putPixel(points[cur].x + centerX, points[cur].y + centerY,
		                thickness);
	}

	if ((i + 1) < points.size()) {
		if (stuck > 30) {
			if (int(count / 10) % 2 == 0) {
				Angel::putPixel(points[i].x + centerX, points[i].y + centerY,
				                thickness);
			} else {
				Angel::putPixel(false_points[i].x + centerX,
				                false_points[i].y + centerY, thickness);
			}
		} else {
			if (cur > 0) {
				Angel::putPixel(points[cur - 1].x + centerX,
				                points[cur - 1].y + centerY, thickness);
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
				                thickness);
			} else {
				Angel::putPixel(false_points[i].y + centerX,
				                false_points[i].x + centerY, thickness);
			}
		} else {
			if (cur > 0) {
				Angel::putPixel(points[cur - 1].y + centerX,
				                points[cur - 1].x + centerY, thickness);
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
				Angel::putPixel(-points[i].x + centerX, points[i].y + centerY);
			} else {
				Angel::putPixel(-false_points[i].x + centerX,
				                false_points[i].y + centerY, thickness);
			}
		} else {
			if (cur > 0) {
				Angel::putPixel(-points[cur - 1].x + centerX,
				                points[cur - 1].y + centerY, thickness);
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
				                thickness);
			} else {
				Angel::putPixel(-false_points[i].y + centerX,
				                false_points[i].x + centerY, thickness);
			}
		} else {
			if (cur > 0) {
				Angel::putPixel(-points[cur - 1].y + centerX,
				                points[cur - 1].x + centerY, thickness);
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
				                thickness);
			} else {
				Angel::putPixel(false_points[i].x + centerX,
				                -false_points[i].y + centerY, thickness);
			}
		} else {
			if (cur > 0) {
				Angel::putPixel(points[cur - 1].x + centerX,
				                -points[cur - 1].y + centerY, thickness);
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
				                thickness);
			} else {
				Angel::putPixel(false_points[i].y + centerX,
				                -false_points[i].x + centerY, thickness);
			}
		} else {
			if (cur > 0) {
				Angel::putPixel(points[cur - 1].y + centerX,
				                -points[cur - 1].x + centerY, thickness);
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
				                thickness);
			} else {
				Angel::putPixel(-false_points[i].x + centerX,
				                -false_points[i].y + centerY, thickness);
			}
		} else {
			if (cur > 0) {
				Angel::putPixel(-points[cur - 1].x + centerX,
				                -points[cur - 1].y + centerY, thickness);
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
				                thickness);
			} else {
				Angel::putPixel(-false_points[i].y + centerX,
				                -false_points[i].x + centerY, thickness);
			}
		} else {
			if (cur > 0) {
				Angel::putPixel(-points[cur - 1].y + centerX,
				                -points[cur - 1].x + centerY, thickness);
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
void Circle::translate(float x, float y){};
void Circle::translate(oglm::vec2 factor){};
void Circle::rotate(float radians, float x, float y){};
void Circle::rotate(float radians, oglm::vec2 factor){};
void Circle::scale(float x, float y){};
void Circle::scale(oglm::vec2 factor){};
bool Circle::isCompleted() { return true; };
void Circle::pause(){};
void Circle::reset(){};
void Circle::increaseSpeed(float speed){};
void Circle::decreaseSpeed(float speed){};
