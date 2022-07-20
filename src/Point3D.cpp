#include "Point3D.hpp"
#include "Angel.hpp"
#include "transform.hpp"
#include <iostream>

Point3D::Point3D(int x, int y, int z):x(x), y(y), z(z){

}

void Point3D::draw(){
    oglm::mat4<float> mrix = oglm::perspective(50.0f, 2.0f, 1.0f, 150.0f);

    // std::vector<float> vvv = oglm::mat4<float>(1) * std::vector<float>{4, 5, 6, 7};

    // std::cout << mrix << std::endl;

    // Angel::putPixel(xp, yp, 5);
}