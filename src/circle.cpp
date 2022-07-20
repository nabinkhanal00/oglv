#include "Line.hpp"
#include "Circle.hpp"
#include "Color.hpp"
#include "Shape2D.hpp"
#include <iostream>
Circle::Circle(int x0, int y0, int r, unsigned int t)
    : thickness(t), frameCount(20) {
    centerX = x0;
    centerY = y0;
    radius = r;
    int x = 0, y = r;
    int p = 1 - r;
    while (y >= x) {
        points.push_back(oglm::vec2<int>(x, y));
        if (p >= 0) {
            y -= thickness;
            p -= 2 * y;
        }
        x += thickness;
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
    Line l1(-Angel::getWidth(), -Angel::getHeight(),Angel::getWidth(), Angel::getHeight(),1);
    l1.draw();
    Line l2(-Angel::getWidth(), Angel::getHeight(),Angel::getWidth(), -Angel::getHeight(),1);
    l2.draw();
    for (int cur = 0; cur < i; cur++) {
        Angel::putPixel(points[cur].x + centerX, points[cur].y + centerY,
                       thickness);
    }
    for (int cur = 0; cur < i; cur++) {
        Angel::putPixel(points[cur].y + centerX, points[cur].x + centerY,
                       thickness);
    }
    for (int cur = 0; cur < i; cur++) {
        Angel::putPixel(-points[cur].x + centerX, points[cur].y + centerY,
                       thickness);
    }
    for (int cur = 0; cur < i; cur++) {
        Angel::putPixel(-points[cur].y + centerX, points[cur].x + centerY,
                       thickness);
    }

    for (int cur = 0; cur < i; cur++) {
        Angel::putPixel(points[cur].x + centerX, -points[cur].y + centerY,
                       thickness);
    }
    for (int cur = 0; cur < i; cur++) {
        Angel::putPixel(points[cur].y + centerX, -points[cur].x + centerY,
                       thickness);
    }
    for (int cur = 0; cur < i; cur++) {
        Angel::putPixel(-points[cur].x + centerX, -points[cur].y + centerY,
                       thickness);
    }
    for (int cur = 0; cur < i; cur++) {
        Angel::putPixel(-points[cur].y + centerX, -points[cur].x + centerY,
                       thickness);
    }
    if (i < points.size()) {
        if (count >= frameCount) {
            i++;
            count = 0;
        } else {
            count++;
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
