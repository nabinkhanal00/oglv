#include "Line.hpp"
#include "Circle.hpp"
#include "Color.hpp"
#include <iostream>
int Circle::count = 0;
unsigned int Circle::frameCount = 60;
int Circle::stuck = 0;
int Circle::i = 0;
Circle::Circle(int x0, int y0, int r, unsigned int t) : thickness(t) {
    centerX = x0;
    centerY = y0;
    radius = r;

    int x = 0;
    int y = radius;
    int p = 1 - radius;
    int tempx = x, tempy = y;
    while (y >= x) {
        points.push_back(oglm::vec2i(x, y));
        false_points.push_back(oglm::vec2i(tempx, tempy));
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
		// oglm::vec4 i = Angel::pers * Angel::view * oglm::vec4(p.x, p.y, 0,
		// 1); std::cout << "i.x " << i.x << " i.y " << i.y << " i.z " << i.z
		//           << " i.w " << i.w << std::endl;
		// i = i / i.w;
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

	static const oglm::vec4 white(1.0f, 1.0f, 1.0f, 1.0f);
	static const oglm::vec4 blue(0.0f, 0.0f, 1.0f, 1.0f);
	static const oglm::vec4 red(1.0f, 0.0f, 0.0f, 1.0f);
        static const oglm::vec4 green(0.0f, 1.0f, 0.0f, 1.0f);
        int cur;
        for (cur = 0; cur < i; cur++) {
            Angel::putPixel(false_points[cur].x + centerX,
                            false_points[cur].y + centerY, thickness, blue);
            Angel::putPixel(points[cur].x + centerX, points[cur].y + centerY,
                            thickness, white);
        }

        if ((i + 1) < points.size()) {
            if (stuck > 30) {
                if (int(count / 10) % 2 == 0) {
                    Angel::putPixel(points[i].x + centerX,
                                    points[i].y + centerY, thickness, red);
                } else {
                    Angel::putPixel(false_points[i].x + centerX,
                                    false_points[i].y + centerY, thickness,
                                    blue);
                }
            } else {
                if (cur > 0) {
                    Angel::putPixel(points[cur - 1].x + centerX,
                                    points[cur - 1].y + centerY, thickness,
                                    red);
                }
            }
        }
        for (cur = 0; cur < i; cur++) {
            Angel::putPixel(false_points[cur].y + centerX,
                            false_points[cur].x + centerY, thickness, blue);
            Angel::putPixel(points[cur].y + centerX, points[cur].x + centerY,
                            thickness, white);
        }
        if ((i + 1) < points.size()) {
            if (stuck > 30) {
                if (int(count / 10) % 2 == 0) {
                    Angel::putPixel(points[i].y + centerX,
                                    points[i].x + centerY, thickness, red);
                } else {
                    Angel::putPixel(false_points[i].y + centerX,
                                    false_points[i].x + centerY, thickness,
                                    blue);
                }
            } else {
                if (cur > 0) {
                    Angel::putPixel(points[cur - 1].y + centerX,
                                    points[cur - 1].x + centerY, thickness,
                                    red);
                }
            }
        }
        for (cur = 0; cur < i; cur++) {
            Angel::putPixel(-false_points[cur].x + centerX,
                            false_points[cur].y + centerY, thickness, blue);
            Angel::putPixel(-points[cur].x + centerX, points[cur].y + centerY,
                            thickness, white);
        }
        if ((i + 1) < points.size()) {
            if (stuck > 30) {
                if (int(count / 10) % 2 == 0) {
                    Angel::putPixel(-points[i].x + centerX,
                                    points[i].y + centerY, thickness, red);
                } else {
                    Angel::putPixel(-false_points[i].x + centerX,
                                    false_points[i].y + centerY, thickness,
                                    blue);
                }
            } else {
                if (cur > 0) {
                    Angel::putPixel(-points[cur - 1].x + centerX,
                                    points[cur - 1].y + centerY, thickness,
                                    red);
                }
            }
        }
        for (cur = 0; cur < i; cur++) {
            Angel::putPixel(-false_points[cur].y + centerX,
                            false_points[cur].x + centerY, thickness, blue);
            Angel::putPixel(-points[cur].y + centerX, points[cur].x + centerY,
                            thickness, white);
        }
        if ((i + 1) < points.size()) {
            if (stuck > 30) {
                if (int(count / 10) % 2 == 0) {
                    Angel::putPixel(-points[i].y + centerX,
                                    points[i].x + centerY, thickness, red);
                } else {
                    Angel::putPixel(-false_points[i].y + centerX,
                                    false_points[i].x + centerY, thickness,
                                    blue);
                }
            } else {
                if (cur > 0) {
                    Angel::putPixel(-points[cur - 1].y + centerX,
                                    points[cur - 1].x + centerY, thickness,
                                    red);
                }
            }
        }

        for (cur = 0; cur < i; cur++) {
            Angel::putPixel(false_points[cur].x + centerX,
                            -false_points[cur].y + centerY, thickness, blue);
            Angel::putPixel(points[cur].x + centerX, -points[cur].y + centerY,
                            thickness, white);
        }
        if ((i + 1) < points.size()) {
            if (stuck > 30) {
                if (int(count / 10) % 2 == 0) {
                    Angel::putPixel(points[i].x + centerX,
                                    -points[i].y + centerY, thickness, red);
                } else {
                    Angel::putPixel(false_points[i].x + centerX,
                                    -false_points[i].y + centerY, thickness,
                                    blue);
                }
            } else {
                if (cur > 0) {
                    Angel::putPixel(points[cur - 1].x + centerX,
                                    -points[cur - 1].y + centerY, thickness,
                                    red);
                }
            }
        }
        for (cur = 0; cur < i; cur++) {
            Angel::putPixel(false_points[cur].y + centerX,
                            -false_points[cur].x + centerY, thickness, blue);
            Angel::putPixel(points[cur].y + centerX, -points[cur].x + centerY,
                            thickness, white);
        }
        if ((i + 1) < points.size()) {
            if (stuck > 30) {
                if (int(count / 10) % 2 == 0) {
                    Angel::putPixel(points[i].y + centerX,
                                    -points[i].x + centerY, thickness, red);
                } else {
                    Angel::putPixel(false_points[i].y + centerX,
                                    -false_points[i].x + centerY, thickness,
                                    blue);
                }
            } else {
                if (cur > 0) {
                    Angel::putPixel(points[cur - 1].y + centerX,
                                    -points[cur - 1].x + centerY, thickness,
                                    red);
                }
            }
        }
        for (cur = 0; cur < i; cur++) {
            Angel::putPixel(-false_points[cur].x + centerX,
                            -false_points[cur].y + centerY, thickness, blue);
            Angel::putPixel(-points[cur].x + centerX, -points[cur].y + centerY,
                            thickness, white);
        }
        if ((i + 1) < points.size()) {
            if (stuck > 30) {
                if (int(count / 10) % 2 == 0) {
                    Angel::putPixel(-points[i].x + centerX,
                                    -points[i].y + centerY, thickness, red);
                } else {
                    Angel::putPixel(-false_points[i].x + centerX,
                                    -false_points[i].y + centerY, thickness,
                                    blue);
                }
            } else {
                if (cur > 0) {
                    Angel::putPixel(-points[cur - 1].x + centerX,
                                    -points[cur - 1].y + centerY, thickness,
                                    red);
                }
            }
        }
        for (cur = 0; cur < i; cur++) {
            Angel::putPixel(-false_points[cur].y + centerX,
                            -false_points[cur].x + centerY, thickness, blue);
            Angel::putPixel(-points[cur].y + centerX, -points[cur].x + centerY,
                            thickness, white);
        }
        if ((i + 1) < points.size()) {
            if (stuck > 30) {
                if (int(count / 10) % 2 == 0) {
                    Angel::putPixel(-points[i].y + centerX,
                                    -points[i].x + centerY, thickness, red);
                } else {
                    Angel::putPixel(-false_points[i].y + centerX,
                                    -false_points[i].x + centerY, thickness,
                                    blue);
                }
            } else {
                if (cur > 0) {
                    Angel::putPixel(-points[cur - 1].y + centerX,
                                    -points[cur - 1].x + centerY, thickness,
                                    red);
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
