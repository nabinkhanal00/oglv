#include "Ellipse.hpp"
#include "Color.hpp"
#include "Line.hpp"
#include <iostream>
Ellipse::Ellipse(int x0, int y0, int rx, int ry, unsigned int t)
    : thickness(t), frameCount(20) {
    centerX = x0;
    centerY = y0;
    majX = rx;
    majY = ry;
    float dx, dy, d1, d2 ;
    int x, y;
    x = 0;
    y = ry;
 
    // Initial decision parameter of region 1
    d1 = (ry * ry) - (rx * rx * ry) +
                     (0.25 * rx * rx);
    dx = 2 * ry * ry * x;
    dy = 2 * rx * rx * y;
 
    // For region 1
    while (dx < dy)
    {
        points.push_back(oglm::vec2<int>(x,y));
 
        // Print points based on 4-way symmetry
        // cout << x + xc << " , " << y + yc << endl;
        // cout << -x + xc << " , " << y + yc << endl;
        // cout << x + xc << " , " << -y + yc << endl;
        // cout << -x + xc << " , " << -y + yc << endl;
 
        // Checking and updating value of
        // decision parameter based on algorithm
        if (d1 < 0)
        {
            x++;
            // x+=thickness;
            dx = dx + (2 * ry * ry);
            d1 = d1 + dx + (ry * ry);
        }
        else
        {
            x++;
            // x+=thickness;
            y--;
            // y-=thickness;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d1 = d1 + dx - dy + (ry * ry);
        }
    }
 
    // Decision parameter of region 2
    d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5))) +
         ((rx * rx) * ((y - 1) * (y - 1))) -
          (rx * rx * ry * ry);
 
    // Plotting points of region 2
    while (y >= 0)
    {
 
        points.push_back(oglm::vec2<int>(x,y));
        // Print points based on 4-way symmetry
        // cout << x + xc << " , " << y + yc << endl;
        // cout << -x + xc << " , " << y + yc << endl;
        // cout << x + xc << " , " << -y + yc << endl;
        // cout << -x + xc << " , " << -y + yc << endl;
 
        // Checking and updating parameter
        // value based on algorithm
        if (d2 > 0)
        {
            y--;
            // y-=thickness;
            dy = dy - (2 * rx * rx);
            d2 = d2 + (rx * rx) - dy;
        }
        else
        {
            y--;
            // y-=thickness;
            x++;
            // x += thickness;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d2 = d2 + dx - dy + (rx * rx);
        }
    }
}

void Ellipse::draw() {

    for (auto &i : points) {
        Angel::putPixel(i.x + centerX, i.y + centerY, thickness);
        Angel::putPixel(-i.x + centerX, i.y + centerY, thickness);
        Angel::putPixel(i.x + centerX, -i.y + centerY, thickness);
        Angel::putPixel(-i.x + centerX, -i.y + centerY, thickness);
    }
}

void Ellipse::animate() {
    static int count = 0;
    static int i = 0;
    for (int cur = 0; cur < i; cur++) {
        Angel::putPixel(points[cur].x + centerX, points[cur].y + centerY,
                        thickness);
    }
    for (int cur = 0; cur < i; cur++) {
        Angel::putPixel(-points[cur].x + centerX, points[cur].y + centerY,
                        thickness);
    }

    for (int cur = 0; cur < i; cur++) {
        Angel::putPixel(points[cur].x + centerX, -points[cur].y + centerY,
                        thickness);
    }
    for (int cur = 0; cur < i; cur++) {
        Angel::putPixel(-points[cur].x + centerX, -points[cur].y + centerY,
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
void Ellipse::translate(int x, int y){};
void Ellipse::translate(oglm::vec2<int> factor){};
void Ellipse::rotate(int radians, int x, int y){};
void Ellipse::rotate(int radians, oglm::vec2<int> factor){};
void Ellipse::scale(int x, int y){};
void Ellipse::scale(oglm::vec2<int> factor){};
bool Ellipse::isCompleted() { return true; };
void Ellipse::pause(){};
void Ellipse::reset(){};
void Ellipse::increaseSpeed(int speed){};
void Ellipse::decreaseSpeed(int speed){};
